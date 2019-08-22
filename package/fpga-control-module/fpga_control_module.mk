################################################################################
#
# fpga_control_module
#
################################################################################

FPGA_CONTROL_MODULE_VERSION = 0.1
FPGA_CONTROL_MODULE_SITE = $(patsubst %/,%,$(FPGA_CONTROL_MODULE_PKGDIR))
FPGA_CONTROL_MODULE_SITE_METHOD = local

$(eval $(kernel-module))
$(eval $(generic-package))
