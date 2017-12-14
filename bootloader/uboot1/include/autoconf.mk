CONFIG_SYSPT_BASE="0x40"
CONFIG_CMD_FAT=y
CONFIG_IMAPX800=y
CONFIG_SYS_CLK_FREQ=12000000
CONFIG_CMD_ITEST=y
CONFIG_SKIP_MAGIC="0x22330233"
CONFIG_SYS_MAX_NAND_DEVICE=y
CONFIG_SYS_NAND_U_BOOT_DST="CONFIG_SYS_PHY_UBOOT_BASE"
CONFIG_BOARD_OEM="(2)"
CONFIG_SYS_GBL_DATA_SIZE=128
CONFIG_SYS_LONGHELP=y
CONFIG_SYS_NAND_5_ADDR_CYCLE=y
CONFIG_BOARD_HWVER="((0 << 16) | (0 << 8) | 1)"
CONFIG_SYS_LOAD_ADDR="(CONFIG_SYS_SDRAM_BASE + 0x7fc0)"
CONFIG_CMD_XIMG=y
CONFIG_CMD_CACHE=y
CONFIG_BOOTDELAY=0
CONFIG_SYS_NAND_BASE="0x20c50010"
CONFIG_SYS_NAND_RELOC_OFFS="(0x02800000)"
CONFIG_SYS_NAND_RD1_OFFS="(0x1800000)"
CONFIG_SYS_HELP_CMD_WIDTH=8
CONFIG_SYS_PHY_RD_BASE="(CONFIG_SYS_SDRAM_BASE + 0x2000000 - 0x40)"
CONFIG_NR_DRAM_BANKS=y
CONFIG_SYS_CBSIZE=256
CONFIG_SYS_NAND_BACK_LEN="(0x0c000000)"
CONFIG_SYS_64BIT_STRTOUL=y
CONFIG_CMD_CONSOLE=y
CONFIG_AU_CLK_MAGIC="(0xbdbeed00)"
CONFIG_SYS_NAND_U_BOOT_DDRTEST_DST="(0x3ffd8000)"
CONFIG_HAVE_PRELOADER=y
CONFIG_CMD_REGINFO=y
CONFIG_SYS_NAND_ECCSIZE=512
CONFIG_MMC=y
CONFIG_SYS_NAND_ECCSTEPS="(CONFIG_SYS_NAND_PAGE_SIZE / CONFIG_SYS_NAND_ECCSIZE)"
CONFIG_SYS_U_BOOT_MMP_SIZE="(0x00004000)"
CONFIG_CMD_MISC=y
CONFIG_PLUS_KEY_GPIO="GPEDAT"
CONFIG_PRODUCT_LINUX_IMAGE_NAME="uImage"
CONFIG_ZERO_BOOTDELAY_CHECK=y
CONFIG_SYS_NAND_NDISK_OFFS="(0x60000000)"
CONFIG_SYS_NAND_RD2_OFFS="(0x0800000)"
CONFIG_ENV_OFFSET="(0x0400000)"
CONFIG_IMAPX=y
CONFIG_NDISK_FTL=y
CONFIG_HIBERMARK_OFFSET="0x60"
CONFIG_SYS_NAND_BLOCK_SIZE="(512 * 1024)"
CONFIG_GZIP_BATT_FILE="<batt.enUS.bin.gz.h>"
CONFIG_SYS_NAND_UDATA_OFFS="(0x1e800000)"
CONFIG_ENV_OVERWRITE=y
CONFIG_CMD_NET=y
CONFIG_CMD_NFS=y
CONFIG_SYS_NAND_4K_PAGE=y
CONFIG_ENV_SIZE="0x4000"
CONFIG_RESERVED_SKIP_BUFFER="(CONFIG_SYS_SDRAM_BASE + 0x7000000)"
CONFIG_CMD_PING=y
CONFIG_NAND_ENV_DST="(CONFIG_RESV_START + 0xf00000)"
CONFIG_GZIP_LOGO_FILE="<logo_enUS.bin.gz.h>"
CONFIG_SYS_MALLOC_LEN="(1024 * 1024 * 20)"
CONFIG_IROM_VERSION=2885
CONFIG_SYS_PHY_AS_SWAP="(CONFIG_SYS_SDRAM_BASE + 0x6008000)"
CONFIG_INITRD_TAG=y
CONFIG_SYS_NAND_ECCBYTES=9
CONFIG_SYS_NAND_NK1_OFFS="(0x2800000)"
CONFIG_SAM_2_128_264M=y
CONFIG_BOOT_AUTO_ADJUST=y
CONFIG_SYS_NAND_BACK1_OFFS="(0x02800000)"
CONFIG_RESV_PTBUFFER="(CONFIG_RESV_START + 0x800000)"
CONFIG_SYS_NAND_OOBSIZE=128
CONFIG_SYS_NAND_DIRTYMARK=44
CONFIG_PRODUCT_WINCE_IMAGE_NAME="zNK.img"
CONFIG_CMD_SAVEENV=y
CONFIG_BOOTSTAT_USB="0x000b"
CONFIG_SYS_DENALI_FILE="asm/arch/denali_data/denali_init.h"
CONFIG_SYS_BARGSIZE="CONFIG_SYS_CBSIZE"
CONFIG_SYS_PHY_UBOOT_BASE="(CONFIG_RESV_START + 0xc00000 - 0x40)"
CONFIG_SYS_NAND_PAGE_COUNT=128
CONFIG_CMD_NAND=y
CONFIG_SYS_PHY_UBOOT_SWAP="(CONFIG_SYS_SDRAM_BASE + 0x8000)"
CONFIG_OEM_FEATURES=y
CONFIG_SYS_NAND_ECCPOS="{0};"
CONFIG_RESV_LOGO="(CONFIG_RESV_START + 0x600000)"
CONFIG_LOGO_GZIP_H=101
CONFIG_LOGO_GZIP_W=356
CONFIG_SYS_NAND_ECCTOTAL="(CONFIG_SYS_NAND_ECCBYTES * CONFIG_SYS_NAND_ECCSTEPS)"
CONFIG_PRODUCT_ANDROID_SYSIMG_NAME="zSYS.img"
CONFIG_SYS_NAND_U_OFFS="(0x0004000)"
CONFIG_SYS_NAND_NK2_OFFS="(0xa400000)"
CONFIG_CMD_MEMORY=y
CONFIG_SYS_MAXARGS=16
CONFIG_RESV_PG_TB="(0x3fffc000)"
CONFIG_RESET_CHECK=y
CONFIG_CMD_RUN=y
CONFIG_SYS_PBSIZE=384
CONFIG_MOTOR_GPIO="GPODAT"
CONFIG_MOTOR_GPIO_NUM=9
CONFIG_BOOTSTAT_U0="0xffff"
CONFIG_BOOTSTAT_U1="0x0001"
CONFIG_BOOTSTAT_U2="0x0002"
CONFIG_IMAP_MMC=y
CONFIG_SYS_DISK_iNAND=y
CONFIG_RECOVERY_KEY2_GPIO_NAME="BACK"
CONFIG_RESV_LCD_BASE="(CONFIG_RESV_START + 0x200000)"
CONFIG_SYS_NAND_SPL_OFFS="(0x0000000)"
CONFIG_SUPPORT_VFAT=y
CONFIG_OEM_UPDATE_PASSWORD="infotm"
CONFIG_RESV_LCD_BASE_1="(CONFIG_RESV_START + 0x400000)"
CONFIG_CMDLINE_EDITING=y
CONFIG_RECOVERY_KEY2_GPIO_NUM=5
CONFIG_SYS_NAND_U_BOOT_SIZE="(512 * 1024)"
CONFIG_SYS_CONSOLE_IS_IN_ENV=y
CONFIG_ENV_IS_IN_INFOTM=y
CONFIG_RECOVERY_KEY1_GPIO="GPADAT"
CONFIG_SYS_PHY_AS_MAXLEN="0xe000000"
CONFIG_IUW_MAGIC2="0x55497557"
CONFIG_IUW_MAGIC3="0x66497557"
CONFIG_IUW_MAGIC4="0x77497557"
CONFIG_CMD_SETGETDCR=y
CONFIG_PRODUCT_WINCE_FB0="(0x80000000)"
CONFIG_SYS_NAND_MLC=y
CONFIG_BACK_PARTITITION="PARTITION_NUM"
CONFIG_MENU_KEY_GPIO="GPODAT"
CONFIG_LINUX_COMMON=y
CONFIG_CMD_BOOTD=y
CONFIG_SYS_NAND_NK_LEN="(0x07c00000)"
CONFIG_NET_MULTI=y
CONFIG_CMD_DNS=y
CONFIG_SYS_CPUSYNC="(0x2)"
CONFIG_CODE_DEBUG=y
CONFIG_SYS_HZ=100000
CONFIG_DOS_PARTITION=y
CONFIG_CLK_800_266=y
CONFIG_RESV_GMAC_BASE="(CONFIG_RESV_START + 0x0)"
CONFIG_SYS_PHY_SPL_BASE="0x3c000200"
CONFIG_RECOVERY_KEY2_GPIO="GPGDAT"
CONFIG_DISPLAY_VERSION=y
CONFIG_CMD_FPGA=y
CONFIG_IDENT_STRING="Shanghai InfoTM Microelectronics Co., Ltd."
CONFIG_RTC_WAKE_SHUT=y
CONFIG_SYS_NAND_BLOCK_LEN="(0x00080000)"
CONFIG_SYS_NAND_RD__OFFS="(0x2000000)"
CONFIG_SYS_NAND_NDISK_LEN="(0x1ff00000)"
CONFIG_RESV_START="(CONFIG_SYS_SDRAM_END - 0x1000000)"
CONFIG_RECOVERY_KEY1_GPIO_NUM=7
CONFIG_SYS_NAND_SYSTEM_OFFS="(0x12800000)"
CONFIG_SYS_BAUDRATE_TABLE="{ 9600, 19200, 38400, 57600, 115200 }"
CONFIG_SYS_PHY_NK_MAXLEN="0x6000000"
CONFIG_BOARD_MAGIC_OFFS="(0x1007fc10)"
CONFIG_SYS_HUSH_PARSER=y
CONFIG_DISABLE_BOOT_OTG=y
CONFIG_MINUS_KEY_GPIO="GPADAT"
CONFIG_SYS_SDRAM_BASE="0x40000000"
CONFIG_SYS_NAND_CACHE_OFFS="(0x5c000000)"
CONFIG_HIBER_ADDRBUF="0x30"
CONFIG_IUW_CLEARDISK="0xE7E7E7E7"
CONFIG_SYS_NAND_LK1_OFFS="(0x1a00000)"
CONFIG_SYS_PROMPT_HUSH_PS2="> "
CONFIG_CMD_ECHO=y
CONFIG_GENERIC_MMC=y
CONFIG_SYS_NAND_U_BOOT_START="CONFIG_SYS_NAND_U_BOOT_DST"
CONFIG_SYS_NAND_DDRTEST_LEN="(0x00004000)"
CONFIG_AU_CLK_MAGIC_OFFS="(0x1007fc00)"
CONFIG_SYS_NAND_UDATA_LEN="(0x3d800000)"
CONFIG_EXTRA_ENV_SETTINGS="stdin=serial\0stdout=serial\0stderr=serial\0bootargs=console=ttyAMA3,115200\0verify=no\0bootcmd=mmc dev 1; fatload mmc 1:1 40007fc0 uimage; fatload mmc 1:1 40ffffc0 ramdisk.img; bootm 40007fc0 40ffffc0\0"
CONFIG_SYS_SDRAM_END="(CONFIG_SYS_SDRAM_BASE + PHYS_SDRAM_1_SIZE)"
CONFIG_BAUDRATE=115200
CONFIG_FASTBOOT=y
CONFIG_CMDLINE_TAG=y
CONFIG_SYS_NAND_LK2_OFFS="(0x1000000)"
CONFIG_SYS_64BIT_VSPRINTF=y
CONFIG_LOGO_GZIP=y
CONFIG_SYS_DEF_EEPROM_ADDR=0
CONFIG_PARTITIONS=y
CONFIG_MINUS_KEY_GPIO_NUM=5
CONFIG_SYS_MEMTEST_END="CONFIG_RESV_START"
CONFIG_IUW_MAGIC="0x00497557"
CONFIG_BOARD_MAGIC="0xdb6db610"
CONFIG_SYS_U_BOOT_MMP_CODE_START="CONFIG_SYS_NAND_U_BOOT_DDRTEST_DST"
CONFIG_SYS_IMAPX200_DCFG0="(0x000166c2)"
CONFIG_SYS_NAND_U0_OFFS="(0x0008000)"
CONFIG_SYS_NAND_PAGE_SIZE=4096
CONFIG_PLUS_KEY_GPIO_NUM=14
CONFIG_SYS_NO_FLASH=y
CONFIG_RESV_SCRIPT="(CONFIG_RESV_START + 0x800000)"
CONFIG_PRODUCT_LINUX_RVFLAG="(0xad000001)"
CONFIG_MENU_KEY_GPIO_NUM=11
CONFIG_MTD_DEVICE=y
CONFIG_SYS_PHY_NK_BASE="(CONFIG_SYS_SDRAM_BASE + 0x200000 - 0x40)"
CONFIG_CMD_SOURCE=y
CONFIG_SYS_PROMPT="[3. LocalDefence]: "
CONFIG_HWVER_MASK="0xffffff00"
CONFIG_BATT_GZIP_H=300
CONFIG_BATT_GZIP_W=300
CONFIG_AU_MEM_MAGIC="(0xbdbeed01)"
CONFIG_DISPLAY_CPUINFO=y
CONFIG_SYS_PHY_LK_BASE="(CONFIG_SYS_SDRAM_BASE + 0x8000 - 0x40)"
CONFIG_SYS_PHY_NK_SWAP="(CONFIG_SYS_SDRAM_BASE + 0x6200000)"
CONFIG_SETUP_MEMORY_TAGS=y
CONFIG_SYS_MEMTEST_START="CONFIG_SYS_SDRAM_BASE"
CONFIG_CMD_LOADB=y
CONFIG_CMD_LOADS=y
CONFIG_SYS_NAND_U1_OFFS="(0x0100000)"
CONFIG_CMD_IMI=y
CONFIG_SYS_NAND_SYSTEM_LEN="(0x0c000000)"
CONFIG_IMAGE_BASE="0x50"
CONFIG_RESV_LOCTABLE="CONFIG_SYS_PHY_NK_SWAP"
CONFIG_AU_MEM_MAGIC_OFFS="(0x1007fc1c)"
CONFIG_ARM=y
CONFIG_RBTREE=y
CONFIG_IMAPX200_INSP="0x46"
CONFIG_CMD_BDI=y
CONFIG_SYS_NAND_iCK_OFFS="(0x1400000)"
CONFIG_LINUX_DEFAULT_BOOTARGS="console=ttyAMA3,115200 vmalloc=304M androidboot.platform=imapx900"
CONFIG_SYS_IMAPX200_APLL="(0x80000041)"
CONFIG_SYS_PHY_BOOT_STAT="(CONFIG_SYS_SDRAM_BASE + 0x4)"
CONFIG_LINUX_RECOVER_BOOTARGS="console=ttyAMA3,115200 vmalloc=304M"
CONFIG_SYS_NAND_SDMA=y
CONFIG_CMD_MMC=y
CONFIG_SYS_NAND_BAD_BLOCK_POS=0
CONFIG_SYS_NAND_U2_OFFS="(0x1400000)"
CONFIG_SYS_RESUME_BASE="(CONFIG_SYS_SDRAM_BASE + 0xe0)"
