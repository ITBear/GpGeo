#pragma once

#include "../Geometry/GpGeoShape.hpp"

namespace GPlatform {

class GP_GEO_CORE_API GpGeoToString
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoToString)

public:
    static std::string  SToString   (const GpGeoShape& aShape);
};

}// namespace GPlatform
