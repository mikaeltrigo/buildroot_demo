################################################################################
#
# quantum
#
################################################################################

QUANTUM_VERSION = 1.1
QUANTUM_SITE =  $(patsubst %/,%,$(QUANTUM_PKGDIR))
QUANTUM_SITE_METHOD = local

$(eval $(cmake-package))