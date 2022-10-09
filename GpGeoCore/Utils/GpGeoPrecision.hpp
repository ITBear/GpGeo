#pragma once

#include "../GpGeoCore_global.hpp"

namespace GPlatform {

class GpGeoPrecision
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoPrecision)

public:
    static constexpr double     SEqualDelta (void) noexcept {return 0.000001;}
};

}//namespace GPlatform
