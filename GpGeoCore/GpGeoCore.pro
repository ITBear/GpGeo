# ----------- Config -----------
TEMPLATE        = lib
#CONFIG        += staticlib
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=c3d3f469-2327-47aa-b6d0-951ff923bcff
PACKET_NAME     = GpGeoCore
DEFINES        += GP_GEO_CORE_LIBRARY
_VER_MAJ        = 2
_VER_MIN        = 1
_VER_PAT        = 5
DIR_LEVEL       = ./../..

include($$DIR_LEVEL/../QtGlobalPro.pri)

# ----------- Libraries -----------
os_windows{
	LIBS += -lGpUtils$$TARGET_POSTFIX
}

os_linux{
}

# ----------- Sources and headers -----------
SOURCES += \
	Geometry/GpGeoAABB.cpp \
	Geometry/GpGeoHash.cpp \
	Geometry/GpGeoPolyline.cpp \
	Geometry/GpGeoShape.cpp \
	Geometry/GpGeoShapeCache.cpp \
	Geometry/GpGeoShapeType.cpp \
	GpGeoCoreLib.cpp \
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
	GpGeoCoreLib.hpp \
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
