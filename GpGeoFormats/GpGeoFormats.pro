TEMPLATE = subdirs

os_linux {
	SUBDIRS += \
		./EsriShape
} else:os_android {
	SUBDIRS += \
		./EsriShape
} else:os_ios {
	SUBDIRS += \
		./EsriShape
} else:os_windows {
	SUBDIRS += \
		./EsriShape
} else:os_macx {
	SUBDIRS += \
		./EsriShape
} else:os_browser {
	SUBDIRS +=
} else {
	error("Unknown OS. Set CONFIG+=... one of values: os_linux, os_android, os_ios, os_windows, os_macx, os_browser, os_baremetal")
}

CONFIG += ordered
