################################################################################
#
# quantum
#
################################################################################

QUANTUM_VERSION = 2935c60f8ac471ba23373fd456be366fd246e9bf
QUANTUM_SITE_METHOD = git
QUANTUM_SITE = 	https://github.com/mikaeltrigo/Quantum.git

$(eval $(cmake-package))