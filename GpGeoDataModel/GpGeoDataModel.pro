TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 0
VER_MIN		    = 1
VER_PAT		    = 0
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=382e4189-e50a-451f-88e2-3c4553e2c5ea
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
DEFINES		   += GP_GEO_DATA_MODEL_LIBRARY
PACKET_NAME     = GpGeoDataModel
DIR_LEVEL       = ./../..

include(../../../QtGlobalPro.pri)

#------------------------------ LIBS BEGIN ---------------------------------
os_windows{
}

os_linux{
}
#------------------------------- LIBS END ----------------------------------

SOURCES += \
    Entities/GpGeoAttribute.cpp \
    Entities/GpGeoElementDesc.cpp \
    Entities/GpGeoElementNameDesc.cpp \
    Entities/GpGeoShapeDesc.cpp \
    Exceptions/GpGeoException.cpp \
    Exceptions/GpGeoExceptionCode.cpp

HEADERS += \
    Entities/GpGeoAttribute.hpp \
    Entities/GpGeoDataModelEntities.hpp \
    Entities/GpGeoElementDesc.hpp \
    Entities/GpGeoElementNameDesc.hpp \
    Entities/GpGeoShapeDesc.hpp \
    Exceptions/GpGeoException.hpp \
    Exceptions/GpGeoExceptionCode.hpp \
    Exceptions/GpGeoExceptions.hpp \
    GpGeoDataModel_global.hpp
