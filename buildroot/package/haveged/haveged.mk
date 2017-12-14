################################################################################
#
# haveged
#
################################################################################

HAVEGED_VERSION = 1.7c
HAVEGED_SITE = http://www.issihosts.com/haveged
HAVEGED_LICENSE = GPLv3+
HAVEGED_LICENSE_FILES = COPYING

define HAVEGED_INSTALL_INIT_SYSV
	$(INSTALL) -m 755 -D buildroot/package/haveged/S21haveged \
		$(TARGET_DIR)/etc/init.d/S21haveged
endef

$(eval $(autotools-package))
