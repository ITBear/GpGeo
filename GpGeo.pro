TEMPLATE = subdirs

os_linux {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel \
		./GpGeoFormats
} else:os_android {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel \
		./GpGeoFormats
} else:os_ios {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel \
		./GpGeoFormats
} else:os_windows {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel \
		./GpGeoFormats
} else:os_macx {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel \
		./GpGeoFormats
} else:os_browser {
	SUBDIRS +=
} else {
    error("Unknown OS")
}

CONFIG += ordered
