################################################################################
#
# LCD Control
#
################################################################################

LCDCONTROL_VERSION = 1.1
LCDCONTROL_SITE = $(patsubst %/,%,$(LCDCONTROL_PKGDIR))
LCDCONTROL_SITE_METHOD = local
LCDCONTROL_PRE_BUILD_HOOKS += FIX_MAKEFILES

define FIX_MAKEFILES
	find $(@D) -name "makefile" -o -name "*.mk" | xargs sed -i -e "s/arm-.*-gcc/\$$\(CC\)/g"
	find $(@D) -name "makefile" -o -name "*.mk" | xargs sed -i -e "s:-I/usr/arm-linux-gnueabi/include::g"
endef

define LCDCONTROL_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)/Release
endef

define LCDCONTROL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/Release/testLCD.elf $(TARGET_DIR)/usr/bin/lcdcontrol
endef

$(eval $(generic-package))
