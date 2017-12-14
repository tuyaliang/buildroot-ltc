#ifndef __SPV_LANGUAGE_RES_H__
#define __SPV_LANGUAGE_RES_H__

enum {
    STRING_ON = 1,
    STRING_OFF,
    STRING_AUTO,
    STRING_OK,
    STRING_CANCLE,
    STRING_DELETE,
    STRING_EXIT,
    STRING_BACK,
    STRING_NA,
    STRING_FILE,
    STRING_FILES,
    STRING_RESTORE_DEFAULT,
    STRING_RESTORE_DEFAULT_SETTINGS,

    //video settings
    STRING_VIDEO_SETTINGS,
    STRING_RESOLUTION,
    STRING_1080FHD,
    STRING_720P_60FPS,
    STRING_720P_30FPS,
    STRING_WVGA,
    STRING_VGA,
    STRING_LOOP_RECORDING,
    STRING_REAR_CAMERA,
    STRING_PIP,
    STRING_WDR,
    STRING_EV_COMPENSATION,
    STRING_POS_2P0,
    STRING_POS_1P5,
    STRING_POS_1P0,
    STRING_POS_0P5,
    STRING_ZERO,
    STRING_NEG_0P5,
    STRING_NEG_1P0,
    STRING_NEG_1P5,
    STRING_NEG_2P0,
    STRING_RECORD_AUDIO,
    STRING_DATE_STAMP,
    STRING_GSENSOR,
    STRING_ADAS,
    STRING_ADAS_CALIBRATE,
    STRING_ADAS_MIDDLE_LINE,
    STRING_ADAS_HOOD_LINE,
    STRING_HIGH,
    STRING_MEDIUM,
    STRING_LOW,
    STRING_PLATE_NUMBER_STAMP,

    //Photo Settings
    STRING_PHOTO_SETTINGS,
    STRING_CAPTURE_MODE,
    STRING_SINGLE,
    STRING_2S_TIMER,
    STRING_5S_TIMER,
    STRING_10S_TIMER,
    STRING_12M,
    STRING_10M,
    STRING_8M,
    STRING_5M,
    STRING_3M,
    STRING_2MHD,
    STRING_1P3M,
    STRING_SEQUENCE,
    STRING_QUALITY,
    STRING_FINE,
    STRING_NORMAL,
    STRING_ECONOMY,
    STRING_SHARPNESS,
    STRING_STRONG,
    STRING_SOFT,
    STRING_WHITE_BALANCE,
    STRING_DAYLIGHT,
    STRING_CLOUDY,
    STRING_TUNGSTEN,
    STRING_FLUORESCENT,
    STRING_COLOR_COLON,
    STRING_COLOR,
    STRING_BLACK_AND_WHITE,
    STRING_SEPIA,
    STRING_ISO_LIMIT,
    STRING_800,
    STRING_400,
    STRING_200,
    STRING_100,
    STRING_ANTI_SHAKING,

    //playback
    STRING_PLAYBACK,

    //setup
    STRING_SETUP,
    STRING_WIFI,
    STRING_DATE_TIME,
    STRING_DATE_SETUP,
    STRING_TIME_SETUP,
    STRING_TIME_AUTO_SYNC,
    STRING_AUTO_POWER_OFF,
    STRING_10_SECONDS,
    STRING_20_SECONDS,
    STRING_30_SECONDS,
    STRING_1_MINUTE,
    STRING_3_MINUTES,
    STRING_5_MINUTES,
    STRING_10_MINUTES,
    STRING_VOLUME,
    STRING_10P,
    STRING_20P,
    STRING_30P,
    STRING_40P,
    STRING_50P,
    STRING_60P,
    STRING_70P,
    STRING_80P,
    STRING_90P,
    STRING_100P,
    STRING_KEY_TONE,
    STRING_LANGUAGE,
    STRING_ENGLISH,
    STRING_CHINESE,
    STRING_CHINESE_TRADITIONAL,
    STRING_FRENCH,
    STRING_ESPANISH,
    STRING_ITALIAN,
    STRING_PORTUGUESE,
    STRING_GERMAN,
    STRING_RUSSIAN,
    STRING_DELAYED_SHUTDOWN,
    STRING_DISPLAY,
    STRING_SLEEP,
    STRING_NEVER,
    STRING_BRIGHTNESS,
    STRING_TV_MODE,
    STRING_PARKING_GUARD,
    STRING_NTSC,
    STRING_PAL,
    STRING_FREQUENCY,
    STRING_50HZ,
    STRING_60HZ,
    STRING_IR_LED,
    STRING_IMAGE_ROTATION,
    STRING_FORMAT,
    STRING_CAMERA_RESET,
    STRING_PLATE_NUMBER_COLON,
    STRING_VERSION,

    STRING_AM,
    STRING_PM,
    STRING_DATE_SETTING,
    STRING_TIME_SETTING,
    STRING_PLATE_NUMBER,
    //new strings
    STRING_WIFI_ON,
    STRING_WIFI_PIN_TIME,
    STRING_WIFI_PIN,
    STRING_WIFI_PIN_DES,
    STRING_PAIR_STOP,
    STRING_DEL_LAST_Q,
    STRING_DEL_ALL_Q,
    STRING_DEL_PROG_S,
    STRING_FORMATE_PROG_S,
    STRING_FORMATE_ERROR,
    STRING_RESET_CAMER_Q,
    STRING_RESET_WIFI_Q,
    STRING_RESET_WIFI_S,
    STRING_SD_EMPTY,
    STRING_SD_FULL,
    STRING_SD_NO,
    STRING_SD_ERROR,
    STRING_SD_ERROR_FORMAT,
    STRING_SD_PREPARE,
    STRING_PLAYBACK_ERROR,
    STRING_USB_CONNECT,
    STRING_CAMERA_BUSY,
    STRING_RESET,
    STRING_FORMAT_Q,

    STRING_END = STRING_FORMAT_Q,
};


extern const char *language_en[];
extern const char *language_zh[];
extern const char *language_tw[];
extern const char *language_fr[];
extern const char *language_es[];
extern const char *language_it[];
extern const char *language_pt[];
extern const char *language_de[];
extern const char *language_ru[];

extern const char **g_language;

#define GETSTRING(string_id) g_language[string_id - 1]

int GetStringId(const char *value);

#endif //__SPV_LANGUAGE_RES
