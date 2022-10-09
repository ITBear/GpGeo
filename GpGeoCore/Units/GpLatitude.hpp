#pragma once

#include "../GpGeoCore_global.hpp"

namespace GPlatform {

class GpGeoUnitType_LATITUDE;

using geo_lat_t = GpUnit<double, 1, GpGeoUnitType_LATITUDE, std::ratio<intmax_t(1), intmax_t(1)> , decltype("geo_lat"_template_str)>;

constexpr geo_lat_t operator"" _geo_lat (const long double aValue) {return geo_lat_t::SMake(geo_lat_t::value_type(aValue));}

}//GPlatform
