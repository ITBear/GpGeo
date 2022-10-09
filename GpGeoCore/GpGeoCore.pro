TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 0
VER_MIN		    = 1
VER_PAT		    = 2
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=c3d3f469-2327-47aa-b6d0-951ff923bcff
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
DEFINES		   += GP_GEO_CORE_LIBRARY
PACKET_NAME     = GpGeoCore
DIR_LEVEL       = ./../..

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
	Geometry/GpGeoShapeType.cpp \
	Utils/GpGeoCoordinateSystem.cpp \
	Utils/GpGeoToString.cpp

HEADERS += \
	Geometry/GpGeoAABB.hpp \
	Geometry/GpGeoGeometry.hpp \
	Geometry/GpGeoHash.hpp \
	Geometry/GpGeoPoint.hpp \
	Geometry/GpGeoPolyline.hpp \
	Geometry/GpGeoShape.hpp \
	Geometry/GpGeoShapeType.hpp \
	GpGeoCore.hpp \
	GpGeoCore_global.hpp \
	Units/GpGeoUnits.hpp \
	Units/GpLatitude.hpp \
	Units/GpLongitude.hpp \
	Utils/CoordinateConverters/GpGeoCC_Wgs84_WebMercator.hpp \
	Utils/CoordinateConverters/GpGeoCoordinateConverter.hpp \
	Utils/CoordinateConverters/GpGeoCoordinateConverters.hpp \
	Utils/GpGeoCoordinateSystem.hpp \
	Utils/GpGeoPrecision.hpp \
	Utils/GpGeoToString.hpp \
	Utils/GpGeoUtils.hpp
