################################################################################
#
# fpga_control_module_qt
#
################################################################################

FPGA_CONTROL_MODULE_QT_VERSION = 0.1
FPGA_CONTROL_MODULE_QT_SITE = $(patsubst %/,%,$(FPGA_CONTROL_MODULE_QT_PKGDIR))
FPGA_CONTROL_MODULE_QT_SITE_METHOD = local

$(eval $(kernel-module))
$(eval $(generic-package))
