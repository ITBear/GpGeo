#pragma once

#include "../GpGeoCore_global.hpp"
#include "../../../GpCore2/GpUtils/Types/Units/GpUnit.hpp"

namespace GPlatform {

class GpGeoUnitType_LONGITUDE;

using geo_lon_t = GpUnit<double, GpGeoUnitType_LONGITUDE, std::ratio<intmax_t(1), intmax_t(1)> , decltype("geo_lon"_template_str)>;

constexpr geo_lon_t operator"" _geo_lon (const long double aValue) {return geo_lon_t::SMake(geo_lon_t::value_type(aValue));}

}//GPlatform
