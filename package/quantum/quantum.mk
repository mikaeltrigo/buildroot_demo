################################################################################
#
# quantum
#
################################################################################

QUANTUM_VERSION = 1.5
QUANTUM_SITE_METHOD = git
QUANTUM_SITE = 	https://github.com/mikaeltrigo/Quantum.git

$(eval $(cmake-package))
