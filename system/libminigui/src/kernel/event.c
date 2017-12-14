/*
** $Id: event.c 13775 2011-06-14 09:15:03Z houhuihua $
**
** event.c: Low level event handling module.
**
** Copyright (C) 2003 ~ 2008 Feynman Software.
** Copyright (C) 1999 ~ 2002 Wei Yongming.
**
** All rights reserved by Feynman Software.
**
** Current maintainer: Wei Yongming.
**
** Create date: 1999.01.11
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

#ifndef __NOUNIX__
#    include <unistd.h>
#    include <sys/time.h>
#endif

#ifdef HAVE_LINUX_KEYBOARD_H
  #include <linux/keyboard.h>
#endif
    
#include "minigui.h"
#include "gdi.h"
#include "window.h"
#include "cliprect.h"
#include "internals.h"
#include "ial.h"
#include "cursor.h"
#include "event.h"
#include "misc.h"

#ifdef _MGRM_PROCESSES
#include "sharedres.h"
#endif

#include "license.h"
#ifdef _MG_ENABLE_LICENSE
#   include "../sysres/license/c_files/01_fmsoft.dat.c"
#endif

struct timeval __mg_event_timeout;

static int timeoutusec;
static int repeatusec;
static int dblclicktime;

#ifndef _MGRM_THREADS
static unsigned int timeout_threshold;
static unsigned int repeat_threshold;
static unsigned int timeout_count;
#endif

static void GetDblclickTime(void)
{
    char szValue[11];
    int ms;

    dblclicktime = DEF_MSEC_DBLCLICK / 10;

    if( GetMgEtcValue (MOUSEPARA, MOUSEPARA_DBLCLICKTIME, szValue, 10) < 0 )
        return;

    ms = atoi(szValue);

    if (ms > 0 && ms < 1000) {
        dblclicktime = ms / 10;
    }
}

static void GetTimeout (void)
{
    char szValue [11];
    int mytimeoutusec, myrepeatusec;

    timeoutusec = DEF_USEC_TIMEOUT;
    repeatusec = DEF_REPEAT_TIME;

    if (GetMgEtcValue (EVENTPARA, EVENTPARA_REPEATUSEC, szValue, 10) < 0)
        return;
    myrepeatusec = atoi(szValue);

    if( GetMgEtcValue (EVENTPARA, EVENTPARA_TIMEOUTUSEC, szValue, 10) < 0 )
        return;
    mytimeoutusec = atoi(szValue);

    if (myrepeatusec >= 0 && mytimeoutusec > 0) {
        timeoutusec = mytimeoutusec;
        repeatusec = myrepeatusec;
    }
}

/* Mouse event parameters. */
static int oldbutton = 0;
static unsigned int time1;
static unsigned int time2;

/* Key event parameters. */
static unsigned int ke_time;
static unsigned char oldkeystate [MGUI_NR_KEYS + 1];
static unsigned char olddownkey = 0;
static DWORD status;
static int alt1 = 0;               /* left alt key state */
static int alt2 = 0;               /* right alt key state */
static int capslock = 0;           /* caps lock key state */
static int esc = 0;                /* escape scan code detected? */
static int caps_off = 1;           /* 1 = normal position, 0 = depressed */
static int numlock = 0;            /* number lock key state */
static int num_off = 1;            /* 1 = normal position, 0 = depressed */
static int slock = 0;              /* scroll lock key state */
static int slock_off = 1;          /* 1 = normal position, 0 = depressed */
static int control1 = 0;           /* left control key state */
static int control2 = 0;           /* right control key state */
static int shift1 = 0;             /* left shift key state */
static int shift2 = 0;             /* left shift key state */

static void ResetMouseEvent(void)
{
#if 0
    IAL_UpdateMouse ();
    oldbutton = IAL_GetMouseButton ();
#else
    oldbutton = 0;
#endif

    time1 = 0;
    time2 = 0;
}

static void ResetKeyEvent(void)
{
#if 0
    memcpy (oldkeystate, IAL_GetKeyboardState (), IAL_UpdateKeyboard ());
#else
    memset (oldkeystate, 0, MGUI_NR_KEYS + 1);
#endif
    olddownkey  = 0;
    status      = 0;
    alt1        = 0;
    alt2        = 0;
    esc         = 0;
    control1    = 0;
    control2    = 0;
    shift1      = 0;
    shift2      = 0;
    capslock    = 0;
    caps_off    = 1;
    numlock     = 0;
    num_off     = 1;
    slock       = 0;
    slock_off   = 1;
    IAL_SetLeds (slock | (numlock << 1) | (capslock << 2));

    __mg_event_timeout.tv_sec = 0;
    __mg_event_timeout.tv_usec = timeoutusec;

#ifndef _MGRM_THREADS
#ifdef _MGRM_PROCESSES
    SHAREDRES_TIMEOUT = __mg_event_timeout;
    SHAREDRES_SHIFTSTATUS = status;
#endif

    timeout_threshold = timeoutusec / 10000;
    repeat_threshold = repeatusec / 10000;
    timeout_count = timeout_threshold;
#endif
}

/* 
 * default long pressed and always pressed value
 * The default long press handling disabled at startup.
 */
unsigned int __mg_key_longpress_time = 0;
unsigned int __mg_key_alwayspress_time = DEF_APRESS_TIME;
unsigned int __mg_interval_time = DEF_INTERVAL_TIME;

static void treat_longpress (PKEYEVENT ke, unsigned int interval)
{
    static unsigned int starttime;
    static int flag1 = 0, flag2 = 1; /*flag1: longpress flags*/
    unsigned int maxctime;

    maxctime = (__mg_key_longpress_time < __mg_key_alwayspress_time)
            ? __mg_key_longpress_time : __mg_key_alwayspress_time;

    if (__mg_key_longpress_time == 0 || interval < maxctime) {
        flag1 = 0; 
        flag2 = 1;
        ke->event = KE_KEYDOWN;
        return;
    }

    if (maxctime < __mg_key_alwayspress_time) {
        if (interval >= __mg_key_longpress_time 
                        && interval <= __mg_key_alwayspress_time) {
            if (!flag1) {
                flag1 = 1;
                ke->event = KE_KEYLONGPRESS;
            }
            else
                ke->event = 0;
        }
        else if (interval >= __mg_key_alwayspress_time) {
            if (flag2) {
                flag2 = 0;
                starttime = __mg_timer_counter;
                ke->event = KE_KEYALWAYSPRESS; 
            }
            else if (__mg_timer_counter - starttime < __mg_interval_time) {
                ke->event = 0;
            }
            else {        
                starttime = __mg_timer_counter;
                ke->event = KE_KEYALWAYSPRESS; 
            }
        }
    }
    else {
        if (interval >= __mg_key_alwayspress_time 
                        && interval <= __mg_key_longpress_time) {
            if (flag2) {
                flag2 = 0;
                starttime = __mg_timer_counter;
                ke->event = KE_KEYALWAYSPRESS; 
            }
            else if (__mg_timer_counter - starttime < __mg_interval_time) {
                ke->event = 0;
            }
            else {        
                starttime = __mg_timer_counter;
                ke->event = KE_KEYALWAYSPRESS; 
            }
        }
        else if (interval >= __mg_key_longpress_time) {
            if (!flag1) {
                flag1 = 1;
                ke->event = KE_KEYLONGPRESS;
            }
            else
                ke->event = 0;
        }
    }
}

#ifndef _MGRM_THREADS
BOOL kernel_GetLWEvent (int event, PLWEVENT lwe)
{
    static LWEVENT old_lwe = {0, 0};
    unsigned int interval;
    int button;
    PMOUSEEVENT me = &(lwe->data.me);
    PKEYEVENT ke = &(lwe->data.ke);
    const char* keystate;
    int i;
    int make;       /* 0 = release, 1 = presse */

    if (event == 0) {
        if (__mg_timer_counter >= timeout_count) {

            timeout_count = __mg_timer_counter + repeat_threshold;

            // repeat last event
            if (old_lwe.type == LWETYPE_KEY 
                    && old_lwe.data.ke.event == KE_KEYDOWN) {
                memcpy (lwe, &old_lwe, sizeof (LWEVENT));
                lwe->data.ke.status |= KS_REPEATED;
                return 1;
            }

            if (!(old_lwe.type == LWETYPE_MOUSE
                    && (old_lwe.data.me.event == ME_LEFTDOWN ||
                        old_lwe.data.me.event == ME_RIGHTDOWN ||
                        old_lwe.data.me.event == ME_MIDDLEDOWN))) {
                // reset delay time
                timeout_count = __mg_timer_counter + timeout_threshold;
            }

            // reset delay time
            lwe->type = LWETYPE_TIMEOUT;
            lwe->count = __mg_timer_counter;

            license_on_timeout();

            return 1;
        }
        return 0;
    }

    timeout_count = __mg_timer_counter + timeout_threshold;
    // There was a event occurred.
    if (event & IAL_MOUSEEVENT) {
        if (!IAL_UpdateMouse ())
            return 0;

        lwe->type = LWETYPE_MOUSE;
        if (kernel_RefreshCursor(&me->x, &me->y, &button)) {
            me->event = ME_MOVED;
            time1 = 0;
            time2 = 0;

            if (oldbutton == button)
                return 1;
        }
   
        if ( !(oldbutton & IAL_MOUSE_LEFTBUTTON) && 
              (button & IAL_MOUSE_LEFTBUTTON) )
        {
            license_on_input();

            interval = __mg_timer_counter - time1;
            if (interval <= dblclicktime)
                me->event = ME_LEFTDBLCLICK;
            else
                me->event = ME_LEFTDOWN;
            time1 = __mg_timer_counter;

            goto mouseret;
        }

        if ( (oldbutton & IAL_MOUSE_LEFTBUTTON) && 
             !(button & IAL_MOUSE_LEFTBUTTON) )
        {
            license_on_input();

            me->event = ME_LEFTUP;
            goto mouseret;
        }

        if ( !(oldbutton & IAL_MOUSE_RIGHTBUTTON) && 
              (button & IAL_MOUSE_RIGHTBUTTON) )
        {
            interval = __mg_timer_counter - time2;
            if (interval <= dblclicktime)
                me->event = ME_RIGHTDBLCLICK;
            else
                me->event = ME_RIGHTDOWN;
            time2 = __mg_timer_counter;

            goto mouseret;
        }

        if ( (oldbutton & IAL_MOUSE_RIGHTBUTTON) && 
            !(button & IAL_MOUSE_RIGHTBUTTON) )
        {
            me->event = ME_RIGHTUP;
            goto mouseret;
        }
    }

    if (event & IAL_KEYEVENT) {
        int nr_keys = IAL_UpdateKeyboard ();

        if (nr_keys == 0)
            return 0;

        license_on_input();

        lwe->type = LWETYPE_KEY;
        keystate = IAL_GetKeyboardState ();
        for (i = 1; i < nr_keys; i++) {
            if (!oldkeystate[i] && keystate[i]) {
                 ke->event = KE_KEYDOWN;
                 ke_time =__mg_timer_counter;
                 ke->scancode = i;
                 olddownkey = i;
                 printf("=====key down %d\n", i);
                 break;
            }
            if (oldkeystate[i] && !keystate[i]) {
                 ke->event = KE_KEYUP;
                 ke->scancode = i;
                 printf("=====key up %d\n", i);
                 break;
            }
        }
        if (i == nr_keys) {
            if (olddownkey == 0)
                return 0;
            ke->scancode = olddownkey;
            interval = __mg_timer_counter - ke_time;
            treat_longpress (ke, interval);
            if (ke->event == 0)
                return 0;
        }
        
        make = (ke->event == KE_KEYDOWN)?1:0;

        if (i != nr_keys) {
            unsigned leds;

            switch (ke->scancode) {
                case SCANCODE_CAPSLOCK:
                    if (make && caps_off) {
                        capslock = 1 - capslock;
                        leds = slock | (numlock << 1) | (capslock << 2);
                        IAL_SetLeds (leds);
                        status = (DWORD)leds << 16;
                    }
                    caps_off = 1 - make;
                break;
                    
                case SCANCODE_NUMLOCK:
                    if (make && num_off) {
                        numlock = 1 - numlock;
                        leds = slock | (numlock << 1) | (capslock << 2);
                        IAL_SetLeds (leds);
                        status = (DWORD)leds << 16;
                    }
                    num_off = 1 - make;
                break;
                
                case SCANCODE_SCROLLLOCK:
                    if (make & slock_off) {
                        slock = 1 - slock;
                        leds = slock | (numlock << 1) | (capslock << 2);
                        IAL_SetLeds (leds);
                        status = (DWORD)leds << 16;
                    }
                    slock_off = 1 - make;
                    break;

                case SCANCODE_LEFTCONTROL:
                    control1 = make;
                    break;
                    
                case SCANCODE_RIGHTCONTROL:
                    control2 = make;
                    break;
                    
                case SCANCODE_LEFTSHIFT:
                    shift1 = make;
                    break;
                    
                case SCANCODE_RIGHTSHIFT:
                    shift2 = make;
                    break;
                    
                case SCANCODE_LEFTALT:
                    alt1 = make;
                    break;

                case SCANCODE_RIGHTALT:
                    alt2 = make;
                    break;
                    
            }

            status &= ~(MASK_KS_SHIFTKEYS);

            status |= (DWORD)((capslock << 8) |
                             (numlock << 7)   |
                             (slock << 6)     |
                             (control1 << 5)  |
                             (control2 << 4)  |
                             (alt1 << 3)      |
                             (alt2 << 2)      |
                             (shift1 << 1)    |
                             (shift2));
                             
            // Mouse button status
            if (oldbutton & IAL_MOUSE_LEFTBUTTON)
                status |= KS_LEFTBUTTON;
            else if (oldbutton & IAL_MOUSE_RIGHTBUTTON)
                status |= KS_RIGHTBUTTON;
        }
        ke->status = status;
#ifndef _MGRM_STANDALONE
        SHAREDRES_SHIFTSTATUS = status;
#endif
        memcpy (oldkeystate, keystate, nr_keys);
        memcpy (&old_lwe, lwe, sizeof (LWEVENT));
        return 1;
    } 

    old_lwe.type = 0;
    return 0;

mouseret:
    status &= ~(MASK_KS_BUTTONS);
    oldbutton = button;
    if (oldbutton & IAL_MOUSE_LEFTBUTTON)
        status |= KS_LEFTBUTTON;
    if (oldbutton & IAL_MOUSE_RIGHTBUTTON)
        status |= KS_RIGHTBUTTON;
    me->status = status;
#ifndef _MGRM_STANDALONE
    SHAREDRES_SHIFTSTATUS = status;
#endif
    memcpy (&old_lwe, lwe, sizeof (LWEVENT));
    return 1;
}

#else

BOOL kernel_GetLWEvent (int event, PLWEVENT lwe)
{
    //printf("kernel_GetLWEvent else evt\n");
    static int timeout_count = 0;
    static LWEVENT old_lwe = {0, 0};

    int nr_keys = 0;
    unsigned int interval;
    int button;
    PMOUSEEVENT me = &(lwe->data.me);
    PKEYEVENT ke = &(lwe->data.ke);
    const char* keystate;
    int i;
    int make;       /* 0 = release, 1 = presse */
    
    if (event & IAL_MOUSEEVENT) {
        if (!IAL_UpdateMouse ())
            event &= ~IAL_MOUSEEVENT;
    }
    if (event & IAL_KEYEVENT) {
        if ((nr_keys = IAL_UpdateKeyboard ()) == 0)
            event &= ~IAL_KEYEVENT;
    }
    
    if (event == 0) {
        if (__mg_event_timeout.tv_sec == 0 && __mg_event_timeout.tv_usec == 0) {

            // set repeat time
            __mg_event_timeout.tv_sec = 0;
            __mg_event_timeout.tv_usec = repeatusec;

            // repeat last event
            if (old_lwe.type == LWETYPE_KEY 
                    && old_lwe.data.ke.event == KE_KEYDOWN) {
               memcpy (lwe, &old_lwe, sizeof (LWEVENT));
               lwe->data.ke.status |= KS_REPEATED;
               return 1;
            }

            if (!(old_lwe.type == LWETYPE_MOUSE
                    && (old_lwe.data.me.event == ME_LEFTDOWN ||
                        old_lwe.data.me.event == ME_RIGHTDOWN ||
                        old_lwe.data.me.event == ME_MIDDLEDOWN))) {
                // reset delay time
                __mg_event_timeout.tv_sec = 0;
                __mg_event_timeout.tv_usec = timeoutusec;
            }

            lwe->type = LWETYPE_TIMEOUT;
            lwe->count = ++timeout_count;

            license_on_timeout();

            return 1;
        }

        old_lwe.type = 0;

        return 0;
    }

    timeout_count = 0;
    /* There was an event occurred. */
    if (event & IAL_MOUSEEVENT) {
        //printf("kernel_GetLWEvent evt:IAL_MOUSEEVENT\n");
        lwe->type = LWETYPE_MOUSE;
        if (kernel_RefreshCursor(&me->x, &me->y, &button)) {

            me->event = ME_MOVED;
            time1 = 0;
            time2 = 0;

            if (oldbutton == button)
                return 1;
        }

        if(0)printf("kernel_GetLWEvent oldbutton:%d, button:%d. xy:%d-%d. if4, fengwu add lbtn\n", 
            oldbutton, button, me->x, me->y);

        //if(button == 4) button |= IAL_MOUSE_LEFTBUTTON;
        if(0)
        {
            int tmp = me->x;
            me->x = me->y;
            me->y = tmp;
            printf("kernel_GetLWEvent switch xy:%d-%d\n", me->x, me->y);
            
        }
        
        if ( !(oldbutton & IAL_MOUSE_LEFTBUTTON) && 
              (button & IAL_MOUSE_LEFTBUTTON) )
        {
            license_on_input();

            interval = __mg_timer_counter - time1;
            if (interval <= dblclicktime)
                me->event = ME_LEFTDBLCLICK;
            else
                me->event = ME_LEFTDOWN;
            time1 = __mg_timer_counter;

            goto mouseret;
        }

        if ( (oldbutton & IAL_MOUSE_LEFTBUTTON) && 
             !(button & IAL_MOUSE_LEFTBUTTON) )
        {
            license_on_input();

            me->event = ME_LEFTUP;
            goto mouseret;
        }

        if ( !(oldbutton & IAL_MOUSE_RIGHTBUTTON) && 
              (button & IAL_MOUSE_RIGHTBUTTON) )
        {
            interval = __mg_timer_counter - time2;
            if (interval <= dblclicktime)
                me->event = ME_RIGHTDBLCLICK;
            else
                me->event = ME_RIGHTDOWN;
            time2 = __mg_timer_counter;
            
            goto mouseret;
        }

        if ( (oldbutton & IAL_MOUSE_RIGHTBUTTON) && 
            !(button & IAL_MOUSE_RIGHTBUTTON) )
        {
            me->event = ME_RIGHTUP;
            goto mouseret;
        }
    }
     
    if (event & IAL_KEYEVENT) {
        license_on_input();

        lwe->type = LWETYPE_KEY;
        keystate = IAL_GetKeyboardState ();
        
        for (i = 1; i < nr_keys; i++) {
            if(!oldkeystate[i] && keystate[i]) {
                 ke->event = KE_KEYDOWN;
                 ke_time =__mg_timer_counter;
                 ke->scancode = i;
                 olddownkey = i;
                 break;
            }
            if(oldkeystate[i] && !keystate[i]) {
                 ke->event = KE_KEYUP;
                 ke->scancode = i;
                 break;
            }
        }
        if (i == nr_keys) {
            if (olddownkey == 0)
                return 0;
            ke->scancode = olddownkey;
            interval = __mg_timer_counter - ke_time;
            treat_longpress (ke, interval);
            if (ke->event == 0)
                return 0;
        }
        
        make = (ke->event == KE_KEYDOWN) ? 1 : 0;

        if (i != nr_keys) {
            unsigned leds;

            switch (ke->scancode) {
                case SCANCODE_CAPSLOCK:
                    if (make && caps_off) {
                        capslock = 1 - capslock;
                        leds = slock | (numlock << 1) | (capslock << 2);
                        IAL_SetLeds (leds);
                        status = (DWORD)leds << 16;
                    }
                    caps_off = 1 - make;
                break;
                    
                case SCANCODE_NUMLOCK:
                    if (make && num_off) {
                        numlock = 1 - numlock;
                        leds = slock | (numlock << 1) | (capslock << 2);
                        IAL_SetLeds (leds);
                        status = (DWORD)leds << 16;
                    }
                    num_off = 1 - make;
                break;
                
                case SCANCODE_SCROLLLOCK:
                    if (make & slock_off) {
                        slock = 1 - slock;
                        leds = slock | (numlock << 1) | (capslock << 2);
                        IAL_SetLeds (leds);
                        status = (DWORD)leds << 16;
                    }
                    slock_off = 1 - make;
                    break;

                case SCANCODE_LEFTCONTROL:
                    control1 = make;
                    break;
                    
                case SCANCODE_RIGHTCONTROL:
                    control2 = make;
                    break;
                    
                case SCANCODE_LEFTSHIFT:
                    shift1 = make;
                    break;
                    
                case SCANCODE_RIGHTSHIFT:
                    shift2 = make;
                    break;
                    
                case SCANCODE_LEFTALT:
                    alt1 = make;
                    break;

                case SCANCODE_RIGHTALT:
                    alt2 = make;
                    break;
                    
            }

            status &= ~(MASK_KS_SHIFTKEYS);

            status |= (DWORD)((capslock << 8) |
                             (numlock << 7)   |
                             (slock << 6)     |
                             (control1 << 5)  |
                             (control2 << 4)  |
                             (alt1 << 3)      |
                             (alt2 << 2)      |
                             (shift1 << 1)    |
                             (shift2));
                             
            // Mouse button status
            if (oldbutton & IAL_MOUSE_LEFTBUTTON)
                status |= KS_LEFTBUTTON;
            else if (oldbutton & IAL_MOUSE_RIGHTBUTTON)
                status |= KS_RIGHTBUTTON;
        }
        ke->status = status;
        memcpy (oldkeystate, keystate, nr_keys);
        memcpy (&old_lwe, lwe, sizeof (LWEVENT));
        __mg_event_timeout.tv_sec = 0;
        __mg_event_timeout.tv_usec = timeoutusec;
        return 1;
    } 

    //printf("kernel_GetLWEvent rtn 0;\n");

    old_lwe.type = 0;
    return 0;

mouseret:
    status &= ~(MASK_KS_BUTTONS);
    oldbutton = button;
    if (oldbutton & IAL_MOUSE_LEFTBUTTON)
        status |= KS_LEFTBUTTON;
    if (oldbutton & IAL_MOUSE_RIGHTBUTTON)
        status |= KS_RIGHTBUTTON;
    me->status = status;
    memcpy (&old_lwe, lwe, sizeof (LWEVENT));
    __mg_event_timeout.tv_sec = 0;
    __mg_event_timeout.tv_usec = timeoutusec;
    return 1;
}
#endif

BOOL GUIAPI GetKeyStatus (UINT uKey)
{
#ifdef _MGRM_PROCESSES
    if (!mgIsServer) {
        if (uKey & 0xF000)      // this is a mouse key
            return SHAREDRES_BUTTON & (uKey >> 12) ? TRUE : FALSE;
        return 0;
    }
#endif

    if (uKey & 0xF000)      // this is a mouse key
        return oldbutton & (uKey >> 12) ? TRUE : FALSE;
    else if (uKey <= MGUI_NR_KEYS)
        return oldkeystate [uKey];

    return FALSE;
}

DWORD GUIAPI GetShiftKeyStatus (void)
{
#ifdef _MGRM_PROCESSES
    return SHAREDRES_SHIFTSTATUS;
#else
    return status;
#endif
}

BOOL mg_InitLWEvent (void)
{
    GetDblclickTime ();
    GetTimeout ();

    if (mg_InitIAL ())
        return FALSE;

    ResetMouseEvent();
    ResetKeyEvent();

    return TRUE;
}

void mg_TerminateLWEvent (void)
{
    mg_TerminateIAL ();
}
