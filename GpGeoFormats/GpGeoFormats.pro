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
    error("Unknown OS")
}

CONFIG += ordered
