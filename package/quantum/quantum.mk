################################################################################
#
# quantum
#
################################################################################

QUANTUM_VERSION = 1.1
QUANTUM_SITE =  $(patsubst %/,%,$(QUANTUM_PKGDIR))
QUANTUM_SITE_METHOD = local
QUANTUM_BUILD_CONFIGURATION = Debug
QUANTUM_PRE_BUILD_HOOKS += FIX_MAKEFILES

define FIX_MAKEFILES
	find $(@D) -name "makefile" -o -name "*.mk" | xargs sed -i -e "s/arm-.*-gcc/\$$\(CC\)/g"
	find $(@D) -name "makefile" -o -name "*.mk" | xargs sed -i -e "s:/home/mybbubuntu/workspace/testQuantum:$(@D):g"
	find $(@D) -name "makefile" -o -name "*.mk" | xargs sed -i -e "s/arm-linux-gnueabi-size/size/g"
endef


define QUANTUM_BUILD_CMDS
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)/$(QUANTUM_BUILD_CONFIGURATION)
endef

define QUANTUM_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/$(QUANTUM_BUILD_CONFIGURATION)/testQuantum.elf $(TARGET_DIR)/usr/bin/quantum
endef

$(eval $(generic-package))
