#pragma once

#include <GpCore2/GpUtils/Types/Units/GpUnit.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringTemplateArg.hpp>

namespace GPlatform {

class GpGeoUnitType_LONGITUDE;

using geo_lon_t = GpUnit<double, GpGeoUnitType_LONGITUDE, std::ratio<intmax_t(1), intmax_t(1)> , GpStringTemplateArg<'g','e','o','_','l','o','n'>>;

constexpr geo_lon_t operator"" _geo_lon (const long double aValue) {return geo_lon_t::SMake(geo_lon_t::value_type(aValue));}

}// namespace GPlatform
