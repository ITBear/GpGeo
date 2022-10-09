#pragma once

#include "../../Geometry/GpGeoPoint.hpp"

namespace GPlatform {

class GpGeoCC_Wgs84_WebMercator
{
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoCC_Wgs84_WebMercator)

public:
    //WGS84 -> WebMercator
    constexpr inline static GpGeoPoint  CCForward (const GpGeoPoint& aPointWgs84) noexcept;

    //WebMercator -> WGS84
    constexpr inline static GpGeoPoint  CCBackward (const GpGeoPoint& aPointWebMercator) noexcept;
};

constexpr GpGeoPoint    GpGeoCC_Wgs84_WebMercator::CCForward (const GpGeoPoint& aPointWgs84) noexcept
{
    const double latWgs84 = aPointWgs84.Lat().Value();
    const double lonWgs84 = aPointWgs84.Lon().Value();

    double latWebMercator;
    double lonWebMercator;

    //https://epsg.io/transform#s_srs=4326&t_srs=3857
    {
        latWebMercator = log(tan((90.0 + latWgs84) * double(M_PI) / 360.0)) / (double(M_PI) / 180.0);
        latWebMercator = latWebMercator * (20037508.34 / 180.0);

        lonWebMercator = lonWgs84 * (20037508.34 / 180.0);
    }

    return GpGeoPoint
    (
        geo_lat_t::SMake(latWebMercator),
        geo_lon_t::SMake(lonWebMercator)
    );
}

constexpr GpGeoPoint    GpGeoCC_Wgs84_WebMercator::CCBackward (const GpGeoPoint& aPointWebMercator) noexcept
{
    const double latWebMercator = aPointWebMercator.Lat().Value();
    const double lonWebMercator = aPointWebMercator.Lon().Value();

    double latWgs84;
    double lonWgs84;

    //https://epsg.io/transform#s_srs=3857&t_srs=4326
    {
        latWgs84 = atan(exp(latWebMercator * double(M_PI) / 20037508.34)) * (360.0 / double(M_PI)) - 90.0;
        lonWgs84 = lonWebMercator * (180.0 / 20037508.34);
    }

    return GpGeoPoint
    (
        geo_lat_t::SMake(latWgs84),
        geo_lon_t::SMake(lonWgs84)
    );
}

}//namespace GPlatform
