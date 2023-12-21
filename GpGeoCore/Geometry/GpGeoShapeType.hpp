#pragma once

#include "../GpGeoCore_global.hpp"

#include <GpCore2/GpUtils/Types/Enums/GpEnum.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringOps.hpp>

namespace GPlatform {

GP_ENUM(GP_GEO_CORE_API, GpGeoShapeType,
    UNKNOWN,
    POINTS,
    LINES,
    POLYGONS,
    MIXED
);

}//namespace GPlatform
