# qlibsensors

QLIBSENSORS_VERSION = 1.0.0
QLIBSENSORS_SOURCE =
QLIBSENSORS_SITE  =

QLIBSENSORS_LICENSE =
QLIBSENSORS_LICENSE_FILES = README

QLIBSENSORS_MAINTAINED = YES
QLIBSENSORS_AUTORECONF = YES
QLIBSENSORS_INSTALL_STAGING = YES
QLIBSENSORS_MAKE = make -s
QLIBSENSORS_DEPENDENCIES = 


ifeq ($(BR2_PACKAGE_LIGHT_SENSOR),y)
QLIBSENSORS_CONF_OPT += -DCOMPILE_LIGHT_SENSOR=yes
QLIBSENSORS_CONF_OPT += -DLUDEV=$(BR2_PACKAGE_LIGHT_SENSOR_DEV)
endif

ifeq ($(BR2_PACKAGE_GPS),y)
QLIBSENSORS_CONF_OPT += -DCOMPILE_GPS=yes
QLIBSENSORS_CONF_OPT += -DGPSTTY=$(BR2_PACKAGE_GPS_TTY)  \
	-DGPSSPEED=$(BR2_PACKAGE_GPS_TTY_SPEED)  \
	-DGPSDATA=$(BR2_PACKAGE_GPS_TTY_DATA)  \
	-DGPSSTOP=$(BR2_PACKAGE_GPS_TTY_STOP)
ifeq ($(BR2_PACKAGE_GPS_TTY_PAR_NONE), y)
QLIBSENSORS_CONF_OPT += -DGPSPARNONE=y
endif
ifeq ($(BR2_PACKAGE_GPS_TTY_PAR_EVEN), y)
QLIBSENSORS_CONF_OPT += -DGPSPAREVEN=y
endif
ifeq ($(BR2_PACKAGE_GPS_TTY_PAR_ODD), y)
QLIBSENSORS_CONF_OPT += -DGPSPARODD=y
endif
endif

# install headers
define QLIBSENSORS_POST_INSTALL_STAGING_HEADERS
	mkdir -p $(STAGING_DIR)/usr/include/qsdk
	mkdir -p $(STAGING_DIR)/usr/lib/pkgconfig
	cp -rfv $(QLIBSENSORS_SRCDIR)/include/qsdk/*.h  $(STAGING_DIR)/usr/include/qsdk
	cp -rfv $(QLIBSENSORS_SRCDIR)/qlibsensors.pc  $(STAGING_DIR)/usr/lib/pkgconfig/
endef

QLIBSENSORS_POST_INSTALL_STAGING_HOOKS  += QLIBSENSORS_POST_INSTALL_STAGING_HEADERS

$(eval $(cmake-package))
