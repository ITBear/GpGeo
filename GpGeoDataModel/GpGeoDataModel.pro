# ----------- Config -----------
TEMPLATE        = lib
#CONFIG        += staticlib
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=382e4189-e50a-451f-88e2-3c4553e2c5ea
PACKET_NAME     = GpGeoDataModel
DEFINES        += GP_GEO_DATA_MODEL_LIBRARY
_VER_MAJ        = 2
_VER_MIN        = 1
_VER_PAT        = 5
DIR_LEVEL       = ./../..

include($$DIR_LEVEL/../QtGlobalPro.pri)

# ----------- Libraries -----------
os_windows{
	LIBS += -lGpReflection$$TARGET_POSTFIX
	LIBS += -lGpUtils$$TARGET_POSTFIX
}

os_linux{
}

# ----------- Sources and headers -----------
SOURCES += \
    Entities/GpGeoAttribute.cpp \
    Entities/GpGeoElementDesc.cpp \
    Entities/GpGeoElementNameDesc.cpp \
    Entities/GpGeoShapeDesc.cpp \
    Exceptions/GpGeoException.cpp \
    Exceptions/GpGeoExceptionCode.cpp \
    GpGeoDataModelLib.cpp

HEADERS += \
    Entities/GpGeoAttribute.hpp \
    Entities/GpGeoDataModelEntities.hpp \
    Entities/GpGeoElementDesc.hpp \
    Entities/GpGeoElementNameDesc.hpp \
    Entities/GpGeoShapeDesc.hpp \
    Exceptions/GpGeoException.hpp \
    Exceptions/GpGeoExceptionCode.hpp \
    Exceptions/GpGeoExceptions.hpp \
    GpGeoDataModelLib.hpp \
    GpGeoDataModel_global.hpp
