################################################################################
#
# fpga control
#
################################################################################

LUA_FPGACONTROL_VERSION = 1.0
LUA_FPGACONTROL_SITE = $(patsubst %/,%,$(LUA_FPGACONTROL_PKGDIR))
LUA_FPGACONTROL_SITE_METHOD = local


define LUA_FPGACONTROL_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define LUA_FPGACONTROL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/fpga_access.so $(TARGET_DIR)/usr/lib/lua/5.2/
endef

$(eval $(generic-package))
