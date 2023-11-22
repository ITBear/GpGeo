TEMPLATE        = lib
#CONFIG         += staticlib
VER_MAJ		    = 2
VER_MIN		    = 1
VER_PAT		    = 4
QMAKE_CXXFLAGS += -DGP_MODULE_UUID=382e4189-e50a-451f-88e2-3c4553e2c5ea
QMAKE_CXXFLAGS += -DGP_REFLECTION_STATIC_ADD_TO_MANAGER
PACKET_NAME     = GpGeoDataModel
DIR_LEVEL       = ./../..

DEFINES		   += GP_GEO_DATA_MODEL_LIBRARY
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
    Entities/GpGeoAttribute.cpp \
    Entities/GpGeoElementDesc.cpp \
    Entities/GpGeoElementNameDesc.cpp \
    Entities/GpGeoShapeDesc.cpp \
    Exceptions/GpGeoException.cpp \
    Exceptions/GpGeoExceptionCode.cpp \
    GpGeoDataModel.cpp

HEADERS += \
    Entities/GpGeoAttribute.hpp \
    Entities/GpGeoDataModelEntities.hpp \
    Entities/GpGeoElementDesc.hpp \
    Entities/GpGeoElementNameDesc.hpp \
    Entities/GpGeoShapeDesc.hpp \
    Exceptions/GpGeoException.hpp \
    Exceptions/GpGeoExceptionCode.hpp \
    Exceptions/GpGeoExceptions.hpp \
    GpGeoDataModel.hpp \
    GpGeoDataModel_global.hpp
