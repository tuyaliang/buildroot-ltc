TARGET_PRODUCT_BASE := \
	$(patsubst mini_%,%,$(patsubst full_%,%,$(TARGET_PRODUCT)))

ifeq ($(TARGET_PRODUCT_BASE),pc)
include device/generic/x86/BoardConfig.mk
TARGET_ARCH_VARIANT := x86
endif

ifeq ($(TARGET_PRODUCT_BASE),pc_x86_64)
# There's no device/generic/x86_64/BoardConfig.mk yet, and pulling in
# build/target/board/generic_x86_64/BoardConfig.mk is a bad idea because
# it contains emulator definitions we don't need.
TARGET_NO_BOOTLOADER := true
TARGET_CPU_ABI := x86_64
TARGET_ARCH := x86_64
TARGET_ARCH_VARIANT := x86_64
TARGET_2ND_CPU_ABI := x86
TARGET_2ND_ARCH := x86
TARGET_2ND_ARCH_VARIANT := x86
TARGET_CPU_SMP := true
TARGET_USES_64_BIT_BINDER := true
SMALLER_FONT_FOOTPRINT := true
MINIMAL_FONT_FOOTPRINT := true
BOARD_HAVE_BLUETOOTH := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/generic/common/bluetooth
USE_OPENGL_RENDERER := true
BOARD_USE_LEGACY_UI := true
BOARD_MALLOC_ALIGNMENT := 16
endif

TARGET_NO_RADIOIMAGE := true
TARGET_NO_KERNEL := false

TARGET_BOARD_PLATFORM := pc

TARGET_BOOTLOADER_BOARD_NAME := pc

TARGET_RECOVERY_UI_LIB := librecovery_ui_pc
TARGET_RECOVERY_PIXEL_FORMAT := BGRA_8888

TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_SPARSE_EXT_DISABLED := true

# Forces cache.img to be built
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4

BOARD_CACHEIMAGE_PARTITION_SIZE := 268435456
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 805306368
BOARD_USERDATAIMAGE_PARTITION_SIZE := 536870912

BOARD_FLASH_BLOCK_SIZE := 4096

USE_CAMERA_STUB := false
BOARD_USES_GENERIC_AUDIO := true

BOARD_SEPOLICY_DIRS := device/img/pc/selinux
BOARD_SEPOLICY_UNION := file_contexts pvr.te

MAX_EGL_CACHE_SIZE := 1048576

BOARD_HAL_STATIC_LIBRARIES = libhealthd.$(TARGET_BOARD_PLATFORM)

DALVIK_VM_LIB := libart.so

TARGET_USES_LOGD := true

ifeq ($(TARGET_PRODUCT_BASE),pc)
-include device/img/pc/extras/BoardConfig.mk
endif
