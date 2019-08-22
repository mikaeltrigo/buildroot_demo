################################################################################
#
# quantum
#
################################################################################

QUANTUM_VERSION = 1.1
QUANTUM_SITE =  $(patsubst %/,%,$(QUANTUM_PKGDIR))/Debug
QUANTUM_SITE_METHOD = local

#HELLOWORLD_INSTALL_STAGING = YES

define QUANTUM_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define QUANTUM_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/testQuantum.elf $(TARGET_DIR)/usr/bin/
endef

$(eval $(generic-package))
