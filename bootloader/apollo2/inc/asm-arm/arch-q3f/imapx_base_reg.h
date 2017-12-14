#ifndef __IMAPX_BASE_REG_H
#define __IMAPX_BASE_REG_H


/* XXX U-BOOT XXX */

#define GRAM_BASE_PA     		(0x08018000)
#define DRAM_BASE_PA     		(0x40000000)
#define IRAM_BASE_PA     		(0x08000000)
#define PERI_BASE_PA			(0x20000000)
#define SRAM_BASE_PA			(0x10000000)
#define IROM_BASE_PA			(0x04000000)
#define BOOT_BASE_PA			(0x00000000)
#define DRAM_BASE_SIZE     		(0x40000000)
#define IRAM_BASE_SIZE     		(0x04000000)
#define PERI_BASE_SIZE			(0x0c000000)
#define SRAM_BASE_SIZE			(0x04000000)
#define IROM_BASE_SIZE			(0x04000000)
#define BOOT_BASE_SIZE			(0x04000000)

#define IIS_BASE_ADDR						(PERI_BASE_PA+0x0)
#define CMN_TIMER_BASE_ADDR					(PERI_BASE_PA+0x100000)
#define PWM_TIMER_BASE_ADDR					(PERI_BASE_PA+0x200000)
#define IIC_BASE_ADDR						(PERI_BASE_PA+0x300000)
#define PCM_BASE_ADDR						(PERI_BASE_PA+0x400000)
#define SSP_BASE_ADDR						(PERI_BASE_PA+0x500000)
#define OTF_BASE_ADDR                       (PERI_BASE_PA+0x7580000)//new OneTwoFour(OTF) ssp core
#define UART_BASE_ADDR						(PERI_BASE_PA+0x800000)
#define AUDIOCDEC_BASE_ADDR					(PERI_BASE_PA+0xC00000)
#define TSC_BASE_ADDR						(PERI_BASE_PA+0xD00000)
#define GPIO_BASE_ADDR						(PERI_BASE_PA+0xF00000)
#define PWDT_BASE_ADDR						(PERI_BASE_PA+0x1200000)
#define EMIF_BASE_ADDR						(PERI_BASE_PA+0x1A00000)
#define CPU_BASE_ADDR						(PERI_BASE_PA+0x1B00000)
#define RTC_BASE_ADDR						(PERI_BASE_PA+0x1D00000)
#define SYSMGR_BASE_ADDR					(PERI_BASE_PA+0xD000000)
#define ISP_BASE_ADDR						(PERI_BASE_PA+0x2000000)
#define CAMIF_BASE_ADDR						(PERI_BASE_PA+0x2100000)
#define MIPI_CSI_BASE_ADDR					(PERI_BASE_PA+0x2200000)
#define IDS0_BASE_ADDR						(PERI_BASE_PA+0x2300000)
#define CRYPTO_BASE_ADDR					(PERI_BASE_PA+0x7700000)
#define FODET_BASE_ADDR						(PERI_BASE_PA+0x4000000)
#define IPOST_BASE_ADDR						(PERI_BASE_PA+0x4100000)
#define VENC_BASE_ADDR						(PERI_BASE_PA+0x5000000)
#define USBH_BASE_ADDR						(PERI_BASE_PA+0x7000000)
#define USBO_BASE_ADDR						(PERI_BASE_PA+0x7100000)
#define SD1_BASE_ADDR						(PERI_BASE_PA+0x7200000)
#define SD2_BASE_ADDR						(PERI_BASE_PA+0x7300000)
#define SD0_BASE_ADDR						(PERI_BASE_PA+0x7400000)
#define GDMA_BASE_ADDR						(PERI_BASE_PA+0x7500000)
#define MAC_BASE_ADDR						(PERI_BASE_PA+0x7600000)

/*follow is not user*/
#define MIPI_DSI_BASE_ADDR					0xffffffff
#define NF2_BASE_ADDR						0xffffffff

/* SCU */
#define SCU_BASE_ADDR           (PERI_BASE_PA+0x1B00000)
#define GIC_CPUI_BASE_ADDR      (SCU_BASE_ADDR+0x100)
#define GTIMER_BASE_ADDR        (SCU_BASE_ADDR+0x200)
#define TIMER_WATCHDOG_ADDR     (SCU_BASE_ADDR+0x600)
#define GIC_DISTRIBUTOR_ADDR    (SCU_BASE_ADDR+0x1000)
#define L2_CACHE_BASE_ADDR			(SCU_BASE_ADDR+0x2000)

/* DRAMC */
#define DWC_DDR_UMCTL_BASE_ADDR     (PERI_BASE_PA+0x1a00000)
#define DWC_DDR_PUBL_BASE_ADDR      (PERI_BASE_PA+0x1a08000)

#define I2C0_BASE_ADDR						(IIC_BASE_ADDR)
#define I2C1_BASE_ADDR						(IIC_BASE_ADDR + 0x1000)
#define SSP_BASE_0_ADDR						(SSP_BASE_ADDR)
#define SSP_BASE_1_ADDR						(SSP_BASE_ADDR + 0x1000)
#define SSP_BASE_2_ADDR                    	(SSP_BASE_ADDR + 0x2000)
#define OTF_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x17c00)//new OneTwoFour
#define	UART0_BASE_ADDR						(UART_BASE_ADDR)
#define	UART2_BASE_ADDR						(UART_BASE_ADDR + 0x2000)
#define	UART3_BASE_ADDR						(UART_BASE_ADDR + 0x3000)
#define EMC0_DBASE_ADDR						(EMIF_BASE_ADDR)
#define EMC0_SBASE_ADDR						(EMIF_BASE_ADDR + 0x1000)
#define EMC1_DBASE_ADDR						(EMIF_BASE_ADDR + 0x2000)
#define EMC1_SBASE_ADDR						(EMIF_BASE_ADDR + 0x3000)
#define EMIF_SYSM_ADDR                      (SYSMGR_BASE_ADDR + 0x8400)
#define CPU_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x9800)
#define PAD_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x9000)
#define RTC_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x9c00)
#define CLK_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0xa000)
#define NIF_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0xa400)
#define SYS_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0xac00)
#define G2D_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0xc000)
#define EFUSE_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0xd000)
#define EFUSE_DATA_ADDR						(SYSMGR_BASE_ADDR + 0xd400)
#define EFUSE_WEMU_ADDR						(SYSMGR_BASE_ADDR + 0xe000)
#define IIS_SYSM_ADDR           			(SYSMGR_BASE_ADDR + 0x10000)
#define TIMER_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x10400)
#define PWM_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x10800)
#define I2C_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x10c00)
#define NF2_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x3C000)
#define SATA_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x3C800)
#define SSP_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x11400)
#define UART_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x12000)
#define ADC_SYS_ADDR						(SYSMGR_BASE_ADDR + 0x13400)
#define GPIO_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x13C00)
#define WDT_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x14800)
#define CRYPTO_SYSM_ADDR					(SYSMGR_BASE_ADDR + 0x39c00)
#define GPS_SYSM_ADDR					        (SYSMGR_BASE_ADDR + 0x28400)
#define MMC0_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x39000)
#define MMC1_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x38800)
#define MMC2_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x38c00)
#define USBH_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x38000)
#define OTG_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x38400)
#define GDMA_SYSM_ADDR                      (SYSMGR_BASE_ADDR + 0x39400)
#define MAC_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x39800)
#define VDEC_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x3c400)
#define MIPI_SYSM_ADDR						(SYSMGR_BASE_ADDR + 0x24800)

/* cpu base registers */
#define CPU_CORE_RESET						(CPU_SYSM_ADDR + 0)

/* rtc base registers */
#define SYS_CFG_CMD                        (RTC_SYSM_ADDR + 0x00)
#define SYS_INT_CLR                        (RTC_SYSM_ADDR + 0x04)
#define SYS_INT_ST                         (RTC_SYSM_ADDR + 0x08)
#define SYS_INT_MASK                       (RTC_SYSM_ADDR + 0x0c)
#define SYS_RST_ST                         (RTC_SYSM_ADDR + 0x10)
#define SYS_RST_CLR                        (RTC_SYSM_ADDR + 0x14)
#define SYS_OSC_0                          (RTC_SYSM_ADDR + 0x18)
#define SYS_OSC_1                          (RTC_SYSM_ADDR + 0x1c)
#define SYS_POWUP_ST                       (RTC_SYSM_ADDR + 0x20)
#define SYS_POWUP_CLR                      (RTC_SYSM_ADDR + 0x24)
#define SYS_WAKEUP_MASK                    (RTC_SYSM_ADDR + 0x28)
#define RTC_INFO0							(RTC_SYSM_ADDR + 0x2c)
#define RTC_INFO1							(RTC_SYSM_ADDR + 0x30)
#define RTC_INFO2							(RTC_SYSM_ADDR + 0x34)
#define RTC_INFO3							(RTC_SYSM_ADDR + 0x38)
#define RTC_INFO4							(RTC_SYSM_ADDR + 0x3c)
#define RTC_INFO5							(RTC_SYSM_ADDR + 0x40)
#define RTC_INFO6							(RTC_SYSM_ADDR + 0x44)
#define RTC_INFO7							(RTC_SYSM_ADDR + 0x48)
//#define RTC_INFO(x)							(RTC_SYSM_ADDR + (x * 4) + 0x2c)
#define RTC_INFO(a, b)                 (RTC_SYSM_ADDR + ((a) * 4) + (b? 0x220: 0x2c))
#define RTC_GPDIR				(RTC_SYSM_ADDR + 0x4C)
#define RTC_GPOUTPUT_ST		(RTC_SYSM_ADDR + 0x50)
#define RTC_GPPULL				(RTC_SYSM_ADDR + 0x54)
#define RTC_GPINPUT_ST			(RTC_SYSM_ADDR + 0x58)
#define RTC_GPINT_CTL			(RTC_SYSM_ADDR + 0x5C)
#define RTC_POWMASK			(RTC_SYSM_ADDR + 0x60)
#define RTC_ALARM_SEC0			(RTC_SYSM_ADDR + 0x64)
#define RTC_ALARM_SEC1			(RTC_SYSM_ADDR + 0x68)
#define RTC_ALARM_SEC2			(RTC_SYSM_ADDR + 0x6c)
#define RTC_ALARM_WEEK0			(RTC_SYSM_ADDR + 0x70)
#define RTC_ALARM_WEEK1			(RTC_SYSM_ADDR + 0x74)
#define RTC_ALARM_WEN			(RTC_SYSM_ADDR + 0x78)
#define RTC_SEC0			(RTC_SYSM_ADDR + 0x80)
#define RTC_SEC1			(RTC_SYSM_ADDR + 0x84)
#define RTC_SEC2			(RTC_SYSM_ADDR + 0x88)
#define RTC_SECWEN			(RTC_SYSM_ADDR + 0x8C)
#define RTC_WEEK0			(RTC_SYSM_ADDR + 0x90)
#define RTC_WEEK1			(RTC_SYSM_ADDR + 0x94)
#define RTC_WEEKWEN			(RTC_SYSM_ADDR + 0x98)
#define RTC_MSEC0			(RTC_SYSM_ADDR + 0x9C)
#define RTC_MSEC1			(RTC_SYSM_ADDR + 0xA0)
#define RTC_MSECWEN			(RTC_SYSM_ADDR + 0xA4)
#define RTC_SECR0			(RTC_SYSM_ADDR + 0xA8)
#define RTC_SECR1			(RTC_SYSM_ADDR + 0xAC)
#define RTC_SECR2			(RTC_SYSM_ADDR + 0xB0)
#define RTC_WEEKR0			(RTC_SYSM_ADDR + 0xB4)
#define RTC_WEEKR1			(RTC_SYSM_ADDR + 0xB8)
#define RTC_MSECR0			(RTC_SYSM_ADDR + 0xBC)
#define RTC_MSECR1			(RTC_SYSM_ADDR + 0xC0)
#define RTC_MASK			(RTC_SYSM_ADDR + 0x140)
#define RTC_STAT			(RTC_SYSM_ADDR + 0x144)
#define RTC_CLEAR			(RTC_SYSM_ADDR + 0x148)


/* clock base registers */
#define BUS1_CLK_BASE		(CLK_SYSM_ADDR + 0x130)
#define BUS2_CLK_BASE		(CLK_SYSM_ADDR + 0x140)
#define BUS3_CLK_BASE		(CLK_SYSM_ADDR + 0x150)
#define BUS4_CLK_BASE		(CLK_SYSM_ADDR + 0x160)
#define BUS5_CLK_BASE		(CLK_SYSM_ADDR + 0x170)
#define BUS6_CLK_BASE		(CLK_SYSM_ADDR + 0x180)
#define BUS7_CLK_BASE		(CLK_SYSM_ADDR + 0x190)
#define BUS_CLK_BASE(x)		(CLK_SYSM_ADDR + 0x120 + (x * 0x10))
#define IDS0EITF_CLK_BASE	(CLK_SYSM_ADDR + 0x1a0)
#define IDS0OSD_CLK_BASE	(CLK_SYSM_ADDR + 0x1b0)
#define IDS0TVIF_CLK_BASE	(CLK_SYSM_ADDR + 0x1c0)
#define IDS1EITF_CLK_BASE	(CLK_SYSM_ADDR + 0x1d0)
#define IDS1OSD_CLK_BASE	(CLK_SYSM_ADDR + 0x1e0)
#define IDS1TVIF_CLK_BASE	(CLK_SYSM_ADDR + 0x1f0)
#define MIPIDPHYCFG_CLK_BASE	(CLK_SYSM_ADDR + 0x200)
#define MIPIDPHYREF_CLK_BASE	(CLK_SYSM_ADDR + 0x210)
#define MIPIDPHYPIX_CLK_BASE	(CLK_SYSM_ADDR + 0x220)
#define ISPOSD_CLK_BASE		(CLK_SYSM_ADDR + 0x230)
#define SD0_CLK_BASE		(CLK_SYSM_ADDR + 0x260)
#define SD1_CLK_BASE		(CLK_SYSM_ADDR + 0x250)
#define SD2_CLK_BASE		(CLK_SYSM_ADDR + 0x240)
#define SD_CLK_BASE(x)		(CLK_SYSM_ADDR + 0x260 - (x * 0x10))
#define NFECC_CLK_BASE		(CLK_SYSM_ADDR + 0x270)
#define HDMI_CLK_BASE		(CLK_SYSM_ADDR + 0x280)
#define UART_CLK_BASE		(CLK_SYSM_ADDR + 0x290)
#define SSP_CLK_BASE		(CLK_SYSM_ADDR + 0x2a0)
#define AUDIO_CLK_BASE		(CLK_SYSM_ADDR + 0x2b0)
#define USBREF_CLK_BASE		(CLK_SYSM_ADDR + 0x2c0)
#define CLKOUT0_CLK_BASE	(CLK_SYSM_ADDR + 0x2d0)
#define CLKOUT1_CLK_BASE	(CLK_SYSM_ADDR + 0x2e0)
#define SATAPHY_CLK_BASE	(CLK_SYSM_ADDR + 0x2f0)
#define CAMOCLK_CLK_BASE	(CLK_SYSM_ADDR + 0x300)
#define DDRPHY_CLK_BASE		(CLK_SYSM_ADDR + 0x310)
#define CRYPTO_CLK_BASE		(CLK_SYSM_ADDR + 0x320)
#define ADC_CLK_BASE			(CLK_SYSM_ADDR + 0x330)


#define FABRIC_CLK_BASE     (CLK_SYSM_ADDR + 0x350)
#define APB_CLK_BASE_NEW	(CLK_SYSM_ADDR + 0x360)
#define APB_CLK_BASE			0


#define AXI_CLK_BASE			1
#define CRYSTAL_CLK_BASE		2
#define CPUP_CLK_BASE			3

#define PLL_A					0
#define PLL_D					1
#define PLL_E					2
#define PLL_V					3

#define SYS_SOFT_RESET(x)            (x + 0x00)     /* soft reset register */
#define SYS_CLOCK_GATE_EN(x)         (x + 0x04)     /* clock gated enable register */
#define SYS_POWER_CONTROL(x)         (x + 0x08)     /* power control register */
#define SYS_BUS_MANAGER(x)           (x + 0x0c)     /* bus manager register */
#define SYS_BUS_QOS_MANAGER0(x)      (x + 0x10)     /* bus QOS manager register */
#define SYS_BUS_QOS_MANAGER1(x)      (x + 0x14)     /* bus QOS manager register */
#define SYS_BUS_ISOLATION_R(x)       (x + 0x18)     /* bus signal isolation */
#define SYS_SYNCRST_CLK_EN(x)      (x + 0x1c)     /* syncreset clock gated enable register */
#define SYS_SPEC_FLAG(x)             (x + 0x20)     /* iram, link mode select for venc*/

/* power control */
#define MODULE_POWERON            0x11
#define MODULE_ISO_CLOSE          0x1
#define MODULE_POWERON_ACK        1
#define MODULE_POWERDOWN          0x10

#define MODULE_BUS_ENABLE         0x3

#endif /* __IMAPX_BASE_REG_H */
