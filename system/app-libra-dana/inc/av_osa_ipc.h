#ifndef _AV_OSA_IPC_H
#define _AV_OSA_IPC_H

#include "info_log.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef long IPC_MSG_DIRECTION;

typedef enum
{
	IPC_MSG_SYS_SERVER=1,
	IPC_MSG_AV_SERVER,
	IPC_MSG_AUDIO,
	IPC_MSG_FILE_PLAY,
	IPC_MSG_FILE_SAVE,
	IPC_MSG_TUTK,
	IPC_MSG_WIFI,
    IPC_MSG_AV_DBG,
    IPC_MSG_TEST,
    IPC_MSG_TEST2,
    IPC_MSG_GUI,
    IPC_MSG_INFT,
}TYPE_IPC_MSG_DIRECTION;

typedef enum
{
	/* 100-199 for sys server */
	IPC_MSG_CMD_SYS_BASE = IPC_MSG_SYS_SERVER*100,
	IPC_MSG_CMD_SYS_NOTITY_DATA_READY,	
	IPC_MSG_CMD_SYS_LONG_REG_REQUEST,
	IPC_MSG_CMD_SYS_LONG_REG_RESPONSE,
    IPC_MSG_CMD_SYS_LONG_DEREG_REQUEST,
    IPC_MSG_CMD_SYS_LONG_DEREG_RESPONSE,
    IPC_MSG_CMD_SYS_SHORT_REG_REQUEST,
    IPC_MSG_CMD_SYS_SHORT_REG_RESPONSE,
    IPC_MSG_CMD_SYS_SAVE_CONFIG,
    IPC_MSG_CMD_SYS_SAVE_JPG,
    IPC_MSG_CMD_SYS_ALARM_PRINT,
    IPC_MSG_CMD_SYS_ALARM_QUERY,
    IPC_MSG_CMD_SYS_ALARM_DELETE,
    IPC_MSG_CMD_SYS_ALARM_MOTION_DETECT,
    IPC_MSG_CMD_SYS_ALARM_SOUND_DETECT,
    IPC_MSG_CMD_SYS_ALARM_TEMPERATURE,
    

	/* 200-299 for av server */
	IPC_MSG_CMD_AV_SVR_BASE = IPC_MSG_AV_SERVER*100,
    IPC_MSG_CMD_AV_SVR_DBG_SAVE,
    IPC_MSG_CMD_AV_SVR_DBG_SHOW_STATISTIC,
    IPC_MSG_CMD_AV_SVR_GUI_START,
    IPC_MSG_CMD_AV_SVR_GUI_STOP,
    IPC_MSG_CMD_AV_SVR_H2_START,
    IPC_MSG_CMD_AV_SVR_H2_STOP,
    IPC_MSG_CMD_AV_SVR_MJPEG_START,
    IPC_MSG_CMD_AV_SVR_MJPEG_STOP,
    IPC_MSG_CMD_AV_SVR_RECO,
    IPC_MSG_CMD_AV_SVR_BURST,
    IPC_MSG_CMD_AV_SVR_DISP_AV,
    IPC_MSG_CMD_AV_SVR_DISP_AV_STOP,
    IPC_MSG_CMD_AV_SVR_DISP_AV_PAUSE,
    IPC_MSG_CMD_AV_SVR_DISP_AV_RESUME,
    IPC_MSG_CMD_AV_SVR_DISP_AV_PREPARE,
    IPC_MSG_CMD_AV_SVR_DISP_PIC,
    IPC_MSG_CMD_AV_SVR_DISP_AV_SPEED,
    IPC_MSG_CMD_AV_FILE_DURATION_REQ,
    IPC_MSG_CMD_AV_FILE_DURATION_RSP,
    IPC_MSG_CMD_AV_SVR_PLAYBACK,
    IPC_MSG_CMD_AV_SVR_MODE_CHANGE,
    IPC_MSG_CMD_AV_AUDIO_PLAY_START,
    IPC_MSG_CMD_AV_AUDIO_PLAY,
    IPC_MSG_CMD_AV_AUDIO_PLAY_CLOSE,
    IPC_MSG_CMD_AV_AUDIO_PLAYFILE,
    IPC_MSG_CMD_AV_CONFIG,
    IPC_MSG_CMD_AV_CONFIG_ALL,

	/* 300-399 for av save */
	IPC_MSG_CMD_FILE_SAVE_BASE = IPC_MSG_FILE_SAVE*100,
    IPC_MSG_CMD_FILE_SAVE_AVI,
    IPC_MSG_CMD_FILE_SAVE_AVI_ALLDAY,
    IPC_MSG_CMD_FILE_SAVE_EXIT, 

	/* 400-499 for tutk */
	IPC_MSG_CMD_TUTK_BASE = IPC_MSG_TUTK*100,

	/* 500-599 for wifi */	
	IPC_MSG_CMD_WIFI_BASE = IPC_MSG_WIFI*100,	

    /* test */
	IPC_MSG_CMD_TEST_BASE = IPC_MSG_TEST*100,
	IPC_MSG_CMD_TEST_AV_DATA,

}TYPE_IPC_MSG_CMD;

#define IPC_MBX_MAX_SIZE 256

typedef struct {
  IPC_MSG_DIRECTION  msg_to;
  IPC_MSG_DIRECTION  msg_from;
  TYPE_IPC_MSG_CMD	 cmd_id;
  unsigned char      data[IPC_MBX_MAX_SIZE-sizeof(IPC_MSG_DIRECTION)-sizeof(TYPE_IPC_MSG_CMD)];
} AV_OSA_IpcMsgHndl;


#ifdef __cplusplus 
extern "C" {
#endif

int AV_OSA_ipcMbxOpen();
int AV_OSA_ipcMbxSend(AV_OSA_IpcMsgHndl *msgData);
int AV_OSA_ipcMbxSendI(TYPE_IPC_MSG_DIRECTION msgTo, TYPE_IPC_MSG_DIRECTION msgFrom, 
    TYPE_IPC_MSG_CMD cmd, int val_in);
int AV_OSA_ipcMbxSendStr(TYPE_IPC_MSG_DIRECTION msgTo, TYPE_IPC_MSG_DIRECTION msgFrom, 
    TYPE_IPC_MSG_CMD cmd, char* val_in);

int AV_OSA_ipcMbxRecvI(TYPE_IPC_MSG_DIRECTION msgTo, TYPE_IPC_MSG_DIRECTION *pMsgFrom_out, 
    TYPE_IPC_MSG_CMD *pCmd_out, int *pVal_out);

int AV_OSA_ipcMbxSend_NBlk(AV_OSA_IpcMsgHndl *msgData);
int AV_OSA_ipcMbxRecv(AV_OSA_IpcMsgHndl * msgData);
int AV_OSA_ipcMbxRecv_NBlk(AV_OSA_IpcMsgHndl * msgData);

#ifdef __cplusplus 
}
#endif

#endif

