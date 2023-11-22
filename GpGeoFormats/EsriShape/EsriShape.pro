TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 2
VER_MIN		    = 1
VER_PAT		    = 4
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=125782a6-e9c7-4235-c7a8-fbb76a1730da
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
PACKET_NAME     = GpGeoFormatsEsriShape
DIR_LEVEL       = ./../../..

DEFINES		   += GP_GEO_FORMATS_ESRI_SHAPE_LIBRARY
DEFINES        += "GP_CURRENT_LIB_VER_MAJ=\\\"$$VER_MAJ\\\""
DEFINES        += "GP_CURRENT_LIB_VER_MIN=\\\"$$VER_MIN\\\""
DEFINES        += "GP_CURRENT_LIB_VER_PAT=\\\"$$VER_PAT\\\""
DEFINES        += "GP_CURRENT_LIB_PACKET_NAME=\\\"$$PACKET_NAME\\\""

include(../../../../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
}

os_linux{
}
#------------------------------- LIBS END ----------------------------------

SOURCES += \
	EsriShape.cpp \
	GpGeoFormatEsriShapeManager.cpp \
	GpGeoFormatEsriShapeManagerFactory.cpp

HEADERS += \
	EsriShape.hpp \
	EsriShape_global.hpp \
	GpGeoFormatEsriShapeManager.hpp \
	GpGeoFormatEsriShapeManagerFactory.hpp
