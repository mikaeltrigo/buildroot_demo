################################################################################
#
# msleep for lua
#
################################################################################

LUA_MSLEEP_VERSION = 1.0
LUA_MSLEEP_SITE = $(patsubst %/,%,$(LUA_MSLEEP_PKGDIR))
LUA_MSLEEP_SITE_METHOD = local


define LUA_MSLEEP_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef

define LUA_MSLEEP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/msleep.so $(TARGET_DIR)/usr/lib/lua/5.2/
endef

$(eval $(generic-package))
