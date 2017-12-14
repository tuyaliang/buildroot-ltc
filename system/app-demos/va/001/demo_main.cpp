/*
 * Copyright (c) 2016~2021 ShangHai InfoTM Ltd all rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Description: Motion detect demos by using histogram info
 *
 * Author:
 *     beca.zhang <beca.zhang@infotm.com>
 *
 * Revision History:
 * -----------------
 * 1.1  08/08/2017 init
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <qsdk/event.h>
#include <qsdk/videobox.h>
#include <linux/fb.h>

#define LINEWIDTH 3
#define JSON_PATH "path.json"
#define RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))
#ifdef HIS_DEBUG
#define HDG(fmt, x...) printf("[VaHis]: "fmt, ##x)
#else
#define HDG(fmt, x...)
#endif

typedef struct {
    void *pFbp;
    int s32FdOsd1;
    uint32_t u32ScreenSize;
    uint32_t u32Xres;
    uint32_t u32Yres;
} ST_MV_INFO;

ST_MV_INFO g_stMvInfo;
uint32_t g_u32TimeStamp;
uint32_t g_u32Vx, g_u32Vy;

/*
 * @brief Draw rectangle
 * @param ps32Ptr   -IN: osd1 fd pointer
 * @param u32X      -IN: rectangle left top x cordinate
 * @param u32Y      -IN: rectangle left top y cordinate
 * @param u32W      -IN: rectangle width
 * @param u32H      -IN: rectangle height
 * @param u32Color  -IN: rectangle color
 * @return void
 */
static void DrawRectangle(int *ps32Ptr, uint32_t u32X, uint32_t u32Y,
        uint32_t u32W, uint32_t u32H, uint32_t u32Color)
{
    uint32_t i, j;

    for (i = 0; i < u32W; i++)
    {
        for (j = 0; j < LINEWIDTH; j++)
        {
            if (((u32Y + j) * g_stMvInfo.u32Xres + u32X + i)
                    <= g_stMvInfo.u32Xres * g_stMvInfo.u32Yres -1)
            {
                *(ps32Ptr + (u32Y + j) * g_stMvInfo.u32Xres + u32X + i)
                    = RGB32BIT(u32Color >> 24, (u32Color >> 16) & 0xff,
                    (u32Color >> 8) & 0xff, u32Color & 0xff);
            }
            if (((u32Y + j + u32H) * g_stMvInfo.u32Xres + u32X + i)
                    <= g_stMvInfo.u32Xres * g_stMvInfo.u32Yres -1)
            {
                *(ps32Ptr + (u32Y + j + u32H) * g_stMvInfo.u32Xres + u32X + i)
                    = RGB32BIT(u32Color >> 24, (u32Color >> 16) & 0xff,
                    (u32Color >> 8) & 0xff, u32Color & 0xff);
            }
        }
    }

    for (i = 0; i < u32H; i++)
    {
        for (j = 0; j < LINEWIDTH; j++)
        {
            if (((u32Y + i) * g_stMvInfo.u32Xres + u32X + u32W + j)
                    <= g_stMvInfo.u32Xres * g_stMvInfo.u32Yres -1)
            {
                *(ps32Ptr + (u32Y + i) * g_stMvInfo.u32Xres + u32X + u32W + j)
                    = RGB32BIT(u32Color >> 24, (u32Color >> 16) & 0xff,
                    (u32Color >> 8) & 0xff, u32Color & 0xff);
            }
            if (((u32Y + i) * g_stMvInfo.u32Xres + u32X + j)
                    <= g_stMvInfo.u32Xres * g_stMvInfo.u32Yres -1)
            {
                *(ps32Ptr + (u32Y + i) * g_stMvInfo.u32Xres + u32X + j)
                    = RGB32BIT(u32Color >> 24, (u32Color >> 16) & 0xff,
                    (u32Color >> 8) & 0xff, u32Color & 0xff);
            }
        }
    }
}

/*
 * @brief movement event handler
 * @param event     -IN: event name
 * @param arg       -IN: event args
 * @return void
 */
static void VaHandle(char *ps8Event, void *pArg)
{
    ST_VA_EVENT stEventData;
    int *ps32Ptr = (int *)g_stMvInfo.pFbp;
    uint32_t u32X, u32Y, u32W, u32H;

    if (!strcmp(ps8Event, EVENT_VAMOVE_BLK))
    {
        memcpy(&stEventData, (ST_VA_EVENT *)pArg, sizeof(ST_VA_EVENT));
        alarm(0);
        HDG("blkinfo u32X: %d, u32Y: %d\n", stEventData.x, stEventData.y);
        u32W = g_stMvInfo.u32Xres / 7; //histogram only support 7x7 grid
        u32H = g_stMvInfo.u32Yres / 7;
        u32X = stEventData.x * u32W;
        u32Y = stEventData.y * u32H;
        DrawRectangle(ps32Ptr, u32X, u32Y, u32W, u32H, 0xff0000);
        alarm(1);
        if (g_u32TimeStamp != (uint32_t)stEventData.timestamp)
        {
            g_u32TimeStamp = stEventData.timestamp;
            memset((int *)g_stMvInfo.pFbp, 0x01, g_stMvInfo.u32ScreenSize);
        }
    }
}

/*
 * @brief resource release
 * @param none
 * @return void
 */
static void KillHandler(int u32SigNum)
{
    event_unregister_handler(EVENT_VAMOVE_BLK, VaHandle);
    if (g_stMvInfo.s32FdOsd1)
    {
        close(g_stMvInfo.s32FdOsd1);
    }
    videobox_stop();
    sleep(1);

    //process exit will auto release mmap
    exit(0);
}

/*
 * @brief alarm handler
 * @param none
 * @return none
 */
static void AlarmHandler(int u32SigNum)
{
    memset((int *)g_stMvInfo.pFbp, 0x01, g_stMvInfo.u32ScreenSize);
}

/*
 * @brief osd1 fb init
 * @param none
 * @return void
 */
static void InitFb()
{
    struct fb_var_screeninfo stVInfo;

    g_stMvInfo.s32FdOsd1 = open("/dev/fb1", O_RDWR);
    if (g_stMvInfo.s32FdOsd1 < 0)
    {
        printf("Error: open /dev/fb1 failed\n");
        exit(-1);
    }

    ioctl(g_stMvInfo.s32FdOsd1, FBIOGET_VSCREENINFO, &stVInfo);
    g_stMvInfo.u32Xres = stVInfo.xres;
    g_stMvInfo.u32Yres = stVInfo.yres;
    g_stMvInfo.u32ScreenSize = stVInfo.xres * stVInfo.yres
        * stVInfo.bits_per_pixel / 8;
    g_stMvInfo.pFbp = mmap(0, g_stMvInfo.u32ScreenSize, PROT_READ | PROT_WRITE,
            MAP_SHARED, g_stMvInfo.s32FdOsd1, 0);
    if (g_stMvInfo.pFbp == MAP_FAILED)
    {
        close(g_stMvInfo.s32FdOsd1);
        printf("Error: failed to map framebuffer device to memory.\n");
        exit(-1);
    }
    stVInfo.yoffset = 0;
    ioctl(g_stMvInfo.s32FdOsd1, FBIOPAN_DISPLAY, &stVInfo);
}

/*
 * @brief main function
 * @param s32Argc      -IN: args' count
 * @param ps8Argv      -IN: args
 * @return 0: Success.
 * @return -1: Failure.
 */
int main(int s32Argc, char** ps8Argv)
{
    g_u32Vx = 1920;
    g_u32Vy = 1088;
    if (videobox_repath(JSON_PATH) < 0)
    {
        printf("Error: videobox start failed!\n");
        exit(-1);
    }
    InitFb();
    signal(SIGINT, KillHandler);
    signal(SIGALRM, AlarmHandler);
    event_register_handler(EVENT_VAMOVE_BLK, 0, VaHandle);

    while (1)
    {
        usleep(20000);
    }
    return 0;
}
