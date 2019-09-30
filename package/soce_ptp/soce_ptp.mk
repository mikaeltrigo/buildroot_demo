################################################################################
#
# quantum
#
################################################################################

SOCE_PTP_VERSION = 1.91
SOCE_PTP_SITE_METHOD = git
SOCE_PTP_SITE = 	https://github.com/mikaeltrigo/soce_ptp.git
SOCE_PTP_LICENSE = GPL-2.0+
SOCE_PTP_LICENSE_FILES = COPYING

SOCE_PTP_MAKE_ENV = \
	$(TARGET_MAKE_ENV) \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	KBUILD_OUTPUT=$(STAGING_DIR)

SOCE_PTP_MAKE_OPTS = \
	prefix=/usr \
	EXTRA_CFLAGS="$(TARGET_CFLAGS)" \
	EXTRA_LDFLAGS="$(TARGET_LDFLAGS)"

define SOCE_PTP_BUILD_CMDS
	$(SOCE_PTP_MAKE_ENV) $(MAKE) $(SOCE_PTP_MAKE_OPTS) -C $(@D) all
endef

define SOCE_PTP_INSTALL_TARGET_CMDS
	$(SOCE_PTP_MAKE_ENV) $(MAKE) $(SOCE_PTP_MAKE_OPTS) \
		DESTDIR=$(TARGET_DIR) -C $(@D) install

	$(INSTALL) -D -m 644 $(SOCE_PTP_PKGDIR)/linuxptp.cfg \
		$(TARGET_DIR)/etc/linuxptp.cfg
endef

define SOCE_PTP_INSTALL_INIT_SYSV
	$(INSTALL) -m 755 -D $(SOCE_PTP_PKGDIR)/S65linuxptp \
		$(TARGET_DIR)/etc/init.d/S65linuxptp
endef

define SOCE_PTP_INSTALL_INIT_SYSTEMD
	$(INSTALL) -D -m 644 $(SOCE_PTP_PKGDIR)/linuxptp.service \
		$(TARGET_DIR)/usr/lib/systemd/system/linuxptp.service
	$(INSTALL) -D -m 644 $(SOCE_PTP_PKGDIR)/linuxptp-system-clock.service \
		$(TARGET_DIR)/usr/lib/systemd/system/linuxptp-system-clock.service
	mkdir -p $(TARGET_DIR)/etc/systemd/system/multi-user.target.wants
	ln -sf ../../../../usr/lib/systemd/system/linuxptp.service \
		$(TARGET_DIR)/etc/systemd/system/multi-user.target.wants/linuxptp.service
endef

$(eval $(generic-package))
