################################################################################
#
# LCD Control
#
################################################################################

LCDCONTROL_VERSION = 1.1
LCDCONTROL_SITE = $(patsubst %/,%,$(LCDCONTROL_PKGDIR))/Release
LCDCONTROL_SITE_METHOD = local

#HELLOWORLD_INSTALL_STAGING = YES

define LCDCONTROL_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define LCDCONTROL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/testLCD.elf $(TARGET_DIR)/usr/bin/
endef

$(eval $(generic-package))
