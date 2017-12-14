#ifndef __IMAP_RTC_H__
#define __IMAP_RTC_H__

#include <mach/imap-iomap.h>

#define SYS_CFG_CMD	(0x0)
#define SYS_INT_CLR	(0x4)
#define SYS_INT_ST	(0x8)
#define SYS_INT_MASK	(0xC)
#define SYS_RST_ST	(0x10)
#define SYS_RST_CLR	(0x14)
#define SYS_POWUP_CLR	(0x24)
#define SYS_WAKEUP_MASK	(0x28)
#define SYS_INFO_0	(0x2c)
#define SYS_INFO_1	(0x30)
#define SYS_INFO_2	(0x34)
#define SYS_INFO_3	(0x38)
#define SYS_INFO_4	(0x3c)
#define SYS_INFO_5	(0x40)
#define SYS_INFO_6	(0x44)
#define SYS_INFO_7	(0x48)
#define SYS_RTC_IO_ENABLE (0x4c)
#define SYS_RTC_IO_OUT   (0x50)
#define SYS_RTC_IO_IN    (0x58)
#define SYS_IO_CFG      (0x5c)
#define SYS_POWMASK     (0x60)
#define SYS_ALARM_SEC0	(0x64)
#define SYS_ALARM_SEC1	(0x68)
#define SYS_ALARM_SEC2	(0x6C)
#define SYS_ALARM_WEEK0	(0x70)
#define SYS_ALARM_WEEK1	(0x74)
#define SYS_ALARM_WEN	(0x78)
#define SYS_GP_OUTPUT0	(0x7c)
#define SYS_RTC_SEC0	(0x80)
#define SYS_RTC_SEC1	(0x84)
#define SYS_RTC_SEC2	(0x88)
#define SYS_RTC_SECWEN	(0x8C)
#define SYS_RTC_WEEK0	(0x90)
#define SYS_RTC_WEEK1	(0x94)
#define SYS_RTC_WEEKWEN	(0x98)
#define SYS_RTC_MSEC0	(0x9C)
#define SYS_RTC_MSEC1	(0xA0)
#define SYS_RTC_MSECWEN	(0xA4)
#define SYS_RTC_SECR0	(0xA8)
#define SYS_RTC_SECR1	(0xAC)
#define SYS_RTC_SECR2	(0xB0)
#define SYS_RTC_WEEKR0	(0xB4)
#define SYS_RTC_WEEKR1	(0xB8)
#define SYS_RTC_MSECR0	(0xBC)
#define SYS_RTC_MSECR1	(0xC0)
#define SYS_IO_CFG2     (0x140)

#endif /* __IMAP_RTC_H__ */
