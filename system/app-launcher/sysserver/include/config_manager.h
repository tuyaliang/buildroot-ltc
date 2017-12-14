#ifndef __CONFIG_MANAGER_H__
#define __CONFIG_MANAGER_H__

#include "config_camera.h"
#include "sys_server.h"

#define ERROR_COMMON         -1
#define ERROR_NOT_INITIALIZE -2
#define ERROR_KEY_NOT_EXIST  -3
#define ERROR_SET_FAILED     -4

typedef enum {
    STATUS_WORKING,
    STATUS_LOCATING,
    STATUS_BATTERY,
    STATUS_CAPACITY,
    STATUS_REAR,
    STATUS_RECORDTIME,
} STATUS_CAMERA;

typedef enum {
    ACTION_SHUTTER_PRESS,
    ACTION_FILE_DELETE,
    ACTION_TIME_SET,
    ACTION_WIFI_SET
} ACTION_CAMERA;

extern const char *g_status_keys[];
extern const char *g_action_keys[];

int IsStatusKey(const char *key);
int InitConfigManager(char *file_path);
int DeinitConfigManager();
int GetConfigValue(const char *key, char *value);
int SetConfigValue(const char *key, const char *value, FROM_TYPE type);
int SaveConfigToDisk();
int GetCameraConfig(config_camera *config);

#endif
