TEMPLATE = subdirs

os_linux {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel
} else:os_android {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel
} else:os_ios {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel
} else:os_windows {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel
} else:os_macx {
	SUBDIRS += \
		./GpGeoCore \
		./GpGeoDataModel
} else:os_browser {
	SUBDIRS +=
} else {
	error("Unknown OS. Set CONFIG+=... one of values: os_linux, os_android, os_ios, os_windows, os_macx, os_browser, os_baremetal")
}

CONFIG += ordered
