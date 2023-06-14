#pragma once

#include "../Geometry/GpGeoPoint.hpp"

namespace GPlatform {

class GP_GEO_CORE_API GpGeoGeoidUtils
{
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoGeoidUtils)

public:
    inline static angle_rad_t   SDistanceRad        (const GpGeoPoint& aPointA,
                                                     const GpGeoPoint& aPointB) noexcept;
    inline static meters_t      SDistanceMeters     (const GpGeoPoint& aPointA,
                                                     const GpGeoPoint& aPointB) noexcept;
    static inline angle_rad_t   SMetersToLatAngle   (const geo_lat_t&   aLat,
                                                     const meters_t     aDistance);
};

angle_rad_t GpGeoGeoidUtils::SDistanceRad
(
    const GpGeoPoint& aPointA,
    const GpGeoPoint& aPointB
) noexcept
{
    const double lat1   = aPointA.Lat().Value();
    const double lon1   = aPointA.Lon().Value();
    const double lat2   = aPointB.Lat().Value();
    const double lon2   = aPointB.Lon().Value();

    const double f1 = lat1 * double(M_PI)/180.0;
    const double f2 = lat2 * double(M_PI)/180.0;
    const double df = (lat2-lat1) * double(M_PI)/180.0;
    const double dl = (lon2-lon1) * double(M_PI)/180.0;

    const double a = sin(df/2.0) * sin(df/2.0) + cos(f1) * cos(f2) * sin(dl/2.0) * sin(dl/2.0);
    const double c = 2.0 * atan2(NumOps::SSqrt<double>(a), NumOps::SSqrt<double>(1.0 - a));

    return angle_rad_t::SMake(c);
}

meters_t    GpGeoGeoidUtils::SDistanceMeters
(
    const GpGeoPoint& aPointA,
    const GpGeoPoint& aPointB
) noexcept
{
    const angle_rad_t angle = GpGeoGeoidUtils::SDistanceRad(aPointA, aPointB);

    return meters_t::SMake(GpGeoConstants::SEquatorialRadius().Value() * angle.Value());
}

angle_rad_t GpGeoGeoidUtils::SMetersToLatAngle
(
    const geo_lat_t&    aLat,
    const meters_t      aDistance
)
{
    const double r  = GpGeoConstants::SEquatorialRadius().Value();
    const double h  = r*(1.0 - sin(abs(aLat.Value())));
    const double rs = NumOps::SSqrt<double>(h*(2.0*r - h));
    const double l  = 2.0*M_PI*rs;


    return angle_rad_t::SMake(2.0*M_PI*aDistance.Value() / l);
}

}//namespace GPlatform
