#pragma once

#include "../GpGeoCore_global.hpp"

#include <GpCore2/GpUtils/Types/Units/SI/GpUnitsSI_Length.hpp>

namespace GPlatform {

class GpGeoConstants
{
public:
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoConstants)

public:
    static constexpr double     SEqualDelta         (void) noexcept {return 0.0000001;}
    static constexpr meters_t   SEquatorialRadius   (void) noexcept {return meters_t::SMake(6378137.0);}
};

}// namespace GPlatform
