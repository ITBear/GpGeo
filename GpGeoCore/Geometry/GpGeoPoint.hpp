#pragma once

#include "../Units/GpGeoUnits.hpp"
#include "../Utils/GpGeoPrecision.hpp"

namespace GPlatform {

class GpGeoPointType_UNIT;

class GpGeoPoint final: protected GpUnit<double, 2, GpGeoPointType_UNIT, std::ratio<intmax_t(1), intmax_t(1)> , decltype("geo_lat_lon"_template_str)>
{
public:
    CLASS_DD(GpGeoPoint)

public:
    constexpr inline                GpGeoPoint      (void) noexcept;
    constexpr inline                GpGeoPoint      (const GpGeoPoint& aPoint) noexcept;
    constexpr inline                GpGeoPoint      (GpGeoPoint&& aPoint) noexcept;
    constexpr inline                GpGeoPoint      (const geo_lat_t    aLat,
                                                     const geo_lon_t    aLon) noexcept;
    constexpr                       ~GpGeoPoint     (void) noexcept = default;

    constexpr inline void           Reset           (void) noexcept;

    constexpr inline GpGeoPoint&    operator=       (const GpGeoPoint& aPoint) noexcept;
    constexpr inline GpGeoPoint&    operator=       (GpGeoPoint&& aPoint) noexcept;
    constexpr inline bool           operator==      (const GpGeoPoint& aPoint) const noexcept;

    constexpr geo_lat_t             Lat             (void) const noexcept {return geo_lat_t::SMake(Container()[0]);}
    constexpr geo_lon_t             Lon             (void) const noexcept {return geo_lon_t::SMake(Container()[1]);}
    constexpr void                  SetLat          (const geo_lat_t aLat) noexcept {Container()[0] = aLat.Value();}
    constexpr void                  SetLon          (const geo_lon_t aLon) noexcept {Container()[1] = aLon.Value();}
    constexpr void                  Set             (const geo_lat_t aLat,
                                                     const geo_lon_t aLon) noexcept {SetLat(aLat); SetLon(aLon);}
    constexpr void                  Set             (const GpGeoPoint& aPoint) noexcept {GpUnit::Set(aPoint);}
};

constexpr GpGeoPoint::GpGeoPoint (void) noexcept:
GpUnit()
{
}

constexpr GpGeoPoint::GpGeoPoint (const GpGeoPoint& aPoint) noexcept:
GpUnit(aPoint)
{
}

constexpr GpGeoPoint::GpGeoPoint (GpGeoPoint&& aPoint) noexcept:
GpUnit(std::move(aPoint))
{
}

constexpr GpGeoPoint::GpGeoPoint
(
    const geo_lat_t aLat,
    const geo_lon_t aLon
) noexcept:
GpUnit(container_type{aLat.Value(), aLon.Value()})
{
}

constexpr void  GpGeoPoint::Reset (void) noexcept
{
    SetLat(0.0_geo_lat);
    SetLon(0.0_geo_lon);
}

constexpr GpGeoPoint&   GpGeoPoint::operator= (const GpGeoPoint& aPoint) noexcept
{
    Set(aPoint);
    return *this;
}

constexpr GpGeoPoint&   GpGeoPoint::operator= (GpGeoPoint&& aPoint) noexcept
{
    Set(std::move(aPoint));
    return *this;
}

constexpr bool  GpGeoPoint::operator== (const GpGeoPoint& aPoint) const noexcept
{
    return    NumOps::SIsEqualToDelta(Lat().Value(), aPoint.Lat().Value(), GpGeoPrecision::SEqualDelta())
           && NumOps::SIsEqualToDelta(Lon().Value(), aPoint.Lon().Value(), GpGeoPrecision::SEqualDelta());
}

/*GpGeoPoint    GpGeoPoint::SCentralPoint
(
    const GpGeoPoint& aPointA,
    const GpGeoPoint& aPointB
) noexcept
{
    return GpGeoPoint
    (
        aPointA.Lat() + (aPointB.Lat() - aPointA.Lat())*0.5_geo_lat,
        aPointA.Lon() + (aPointB.Lon() - aPointA.Lon())*0.5_geo_lon
    );
}*/

}//namespace GPlatform
