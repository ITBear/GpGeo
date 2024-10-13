#include <GpGeo/GpGeoCore/Geometry/GpGeoAABB.hpp>
#include <GpGeo/GpGeoCore/Geometry/GpGeoShape.hpp>
#include <GpGeo/GpGeoCore/Geometry/GpGeoPolyline.hpp>
#include <GpGeo/GpGeoCore/Utils/GpGeoGeoidUtils.hpp>

namespace GPlatform {

GpGeoAABB   GpGeoAABB::SFromShape (const GpGeoShape& aShape) noexcept
{
    const GpGeoPolyline::C::Vec::Val& contours = aShape.Contours();

    double  latMin  = 0.0;
    double  latMax  = 0.0;
    double  lonMin  = 0.0;
    double  lonMax  = 0.0;
    bool    isFirst = true;

    for (const GpGeoPolyline& contour: contours)
    {
        const GpGeoPoint::C::Vec::Val& points = contour.Points();

        for (const GpGeoPoint& point: points)
        {
            const double lat = point.Lat().Value();
            const double lon = point.Lon().Value();

            if (!isFirst) [[likely]]
            {
                std::tie(latMin, latMax) = GpNumericOps::SMinMaxFast(latMin, latMax, lat);
                std::tie(lonMin, lonMax) = GpNumericOps::SMinMaxFast(lonMin, lonMax, lon);
            } else
            {
                isFirst = false;
                latMin  = lat;
                lonMin  = lon;
                latMax  = lat;
                lonMax  = lon;
            }
        }
    }

    return GpGeoAABB::SFromMinMax
    (
        {geo_lat_t::SMake(latMin), geo_lon_t::SMake(lonMin)},
        {geo_lat_t::SMake(latMax), geo_lon_t::SMake(lonMax)}
    );
}

GpGeoAABB   GpGeoAABB::SFromPointAndR
(
    const GpGeoPoint&   aSearchPoint,
    const meters_t      aSearchRadius
)
{
    angle_deg_t d = GpGeoGeoidUtils::SMetersToLatAngle(aSearchPoint.Lat(), aSearchRadius*meters_t::SMake(2.0));

    return SFromCentralPoint
    (
        aSearchPoint,
        geo_lat_t::SMake(d.Value()),
        geo_lon_t::SMake(d.Value())
    );
}

}// namespace GPlatform
