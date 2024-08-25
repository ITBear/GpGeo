# ----------- Config -----------
TEMPLATE        = lib
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=125782a6-e9c7-4235-c7a8-fbb76a1730da
PACKET_NAME     = GpGeoFormatsEsriShape
DEFINES        += GP_GEO_FORMATS_ESRI_SHAPE_LIBRARY
_VER_MAJ        = 2
_VER_MIN        = 1
_VER_PAT        = 6
DIR_LEVEL       = ./../../..

include($$DIR_LEVEL/../QtGlobalPro.pri)

release_build_static{
	CONFIG += staticlib
}

# ----------- Libraries -----------
os_windows{
	LIBS += -lGpGeoCore$$TARGET_POSTFIX
	LIBS += -lGpUtils$$TARGET_POSTFIX

	LIBS += -lshp
}

os_linux{
}

# ----------- Sources and headers -----------
SOURCES += \
	EsriShapeLib.cpp \
	GpGeoFormatEsriShapeManager.cpp \
	GpGeoFormatEsriShapeManagerFactory.cpp

HEADERS += \
	EsriShapeLib.hpp \
	EsriShape_global.hpp \
	GpGeoFormatEsriShapeManager.hpp \
	GpGeoFormatEsriShapeManagerFactory.hpp
