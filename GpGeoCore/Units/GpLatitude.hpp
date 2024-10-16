#pragma once

#include <GpCore2/GpUtils/Types/Units/GpUnit.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringTemplateArg.hpp>

namespace GPlatform {

class GpGeoUnitType_LATITUDE;

using geo_lat_t = GpUnit<double, GpGeoUnitType_LATITUDE, std::ratio<intmax_t(1), intmax_t(1)> , GpStringTemplateArg<'g','e','o','_','l','a','t'>>;

constexpr geo_lat_t operator"" _geo_lat (const long double aValue) {return geo_lat_t::SMake(geo_lat_t::value_type(aValue));}

}// namespace GPlatform
