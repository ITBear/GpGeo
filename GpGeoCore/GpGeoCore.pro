TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 2
VER_MIN		    = 1
VER_PAT		    = 4
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=c3d3f469-2327-47aa-b6d0-951ff923bcff
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
PACKET_NAME     = GpGeoCore
DIR_LEVEL       = ./../..

DEFINES		   += GP_GEO_CORE_LIBRARY
DEFINES        += "GP_CURRENT_LIB_VER_MAJ=\\\"$$VER_MAJ\\\""
DEFINES        += "GP_CURRENT_LIB_VER_MIN=\\\"$$VER_MIN\\\""
DEFINES        += "GP_CURRENT_LIB_VER_PAT=\\\"$$VER_PAT\\\""
DEFINES        += "GP_CURRENT_LIB_PACKET_NAME=\\\"$$PACKET_NAME\\\""

include(../../../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
}

os_linux{
}
#------------------------------- LIBS END ----------------------------------

SOURCES += \
	Geometry/GpGeoAABB.cpp \
	Geometry/GpGeoHash.cpp \
	Geometry/GpGeoPolyline.cpp \
	Geometry/GpGeoShape.cpp \
	Geometry/GpGeoShapeCache.cpp \
	Geometry/GpGeoShapeType.cpp \
	GpGeoCore.cpp \
	Utils/GpGeoCoordinateSystem.cpp \
	Utils/GpGeoSmallScaleUtils.cpp \
	Utils/GpGeoToString.cpp

HEADERS += \
	Geometry/GpGeoAABB.hpp \
	Geometry/GpGeoGeometry.hpp \
	Geometry/GpGeoHash.hpp \
	Geometry/GpGeoPoint.hpp \
	Geometry/GpGeoPolyline.hpp \
	Geometry/GpGeoShape.hpp \
	Geometry/GpGeoShapeCache.hpp \
	Geometry/GpGeoShapeCacheImpl.hpp \
	Geometry/GpGeoShapeType.hpp \
	GpGeoCore.hpp \
	GpGeoCore_global.hpp \
	Units/GpGeoUnits.hpp \
	Units/GpLatitude.hpp \
	Units/GpLongitude.hpp \
	Utils/CoordinateConverters/GpGeoCC_Wgs84_WebMercator.hpp \
	Utils/CoordinateConverters/GpGeoCoordinateConverter.hpp \
	Utils/CoordinateConverters/GpGeoCoordinateConverters.hpp \
	Utils/GpGeoConstants.hpp \
	Utils/GpGeoCoordinateSystem.hpp \
	Utils/GpGeoFormatManager.hpp \
	Utils/GpGeoFormatManagerFactory.hpp \
	Utils/GpGeoGeoidUtils.hpp \
	Utils/GpGeoSmallScaleUtils.hpp \
	Utils/GpGeoToString.hpp \
	Utils/GpGeoUtils.hpp
