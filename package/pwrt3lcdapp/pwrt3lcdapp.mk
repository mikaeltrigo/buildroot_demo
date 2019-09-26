################################################################################
#
# pwrt3 lcd app
#
################################################################################

PWRT3LCDAPP_VERSION = e68a956d4f8d5ee1da570e98b5c45b55d0260948
PWRT3LCDAPP_SITE_METHOD = git
PWRT3LCDAPP_SITE = 	https://github.com/mikaeltrigo/pwrt3_lcd_app.git

$(eval $(cmake-package))
