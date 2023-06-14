#pragma once

#include "../Units/GpGeoUnits.hpp"
#include "../Utils/GpGeoConstants.hpp"
#include "../../../GpCore2/GpUtils/Types/Containers/GpContainersT.hpp"
#include "../../../GpGeometry/GpGeometryCore/GpPoint2d.hpp"

namespace GPlatform {

class GpGeoPointType_UNIT;

class GpGeoPoint
{
public:
    CLASS_DD(GpGeoPoint)

public:
    constexpr                           GpGeoPoint          (void) noexcept = default;
    constexpr inline                    GpGeoPoint          (const GpGeoPoint& aPoint) noexcept;
    constexpr inline                    GpGeoPoint          (GpGeoPoint&& aPoint) noexcept;
    constexpr inline                    GpGeoPoint          (const geo_lat_t    aLat,
                                                             const geo_lon_t    aLon) noexcept;

#if  (__cplusplus >= CPP_VERSION_20)
    constexpr                           ~GpGeoPoint         (void) noexcept = default;
#else
                                        ~GpGeoPoint         (void) noexcept = default;
#endif//#if  (__cplusplus >= CPP_VERSION_20)

    constexpr inline void               Reset               (void) noexcept;

    constexpr inline GpGeoPoint&        operator=           (const GpGeoPoint& aPoint) noexcept;
    constexpr inline GpGeoPoint&        operator=           (GpGeoPoint&& aPoint) noexcept;
    constexpr inline bool               operator==          (const GpGeoPoint& aPoint) const noexcept;

    constexpr geo_lat_t                 Lat                 (void) const noexcept {return iLat;}
    constexpr geo_lon_t                 Lon                 (void) const noexcept {return iLon;}
    constexpr GpGeoPoint&               SetLat              (const geo_lat_t aLat) noexcept {iLat = aLat; return *this;}
    constexpr GpGeoPoint&               SetLon              (const geo_lon_t aLon) noexcept {iLon = aLon; return *this;}
    constexpr inline GpGeoPoint&        Set                 (const geo_lat_t aLat,
                                                             const geo_lon_t aLon) noexcept;
    constexpr inline GpGeoPoint&        Set                 (const GpGeoPoint& aPoint) noexcept;

    constexpr GpPoint2d                 AsPoint2D           (void) const noexcept {return GpPoint2d(Lat().Value(), Lon().Value());}
    constexpr inline GpGeoPoint&        FromPoint2D         (const GpPoint2d& aPoint) noexcept;
    static constexpr inline GpGeoPoint  SFromPoint2D        (const GpPoint2d& aPoint) noexcept;

private:
    geo_lat_t       iLat;
    geo_lon_t       iLon;
};

constexpr GpGeoPoint::GpGeoPoint (const GpGeoPoint& aPoint) noexcept:
iLat(aPoint.iLat),
iLon(aPoint.iLon)
{
}

constexpr GpGeoPoint::GpGeoPoint (GpGeoPoint&& aPoint) noexcept:
iLat(std::move(aPoint.iLat)),
iLon(std::move(aPoint.iLon))
{
}

constexpr GpGeoPoint::GpGeoPoint
(
    const geo_lat_t aLat,
    const geo_lon_t aLon
) noexcept:
iLat(aLat),
iLon(aLon)
{
}

constexpr void  GpGeoPoint::Reset (void) noexcept
{
    SetLat(0.0_geo_lat);
    SetLon(0.0_geo_lon);
}

constexpr GpGeoPoint&   GpGeoPoint::Set
(
    const geo_lat_t aLat,
    const geo_lon_t aLon
) noexcept
{
    iLat = aLat;
    iLon = aLon;

    return *this;
}

constexpr GpGeoPoint&   GpGeoPoint::Set (const GpGeoPoint& aPoint) noexcept
{
    iLat = aPoint.iLat;
    iLon = aPoint.iLon;

    return *this;
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
    return    NumOps::SIsEqualToDelta(Lat().Value(), aPoint.Lat().Value(), GpGeoConstants::SEqualDelta())
           && NumOps::SIsEqualToDelta(Lon().Value(), aPoint.Lon().Value(), GpGeoConstants::SEqualDelta());
}

constexpr GpGeoPoint&   GpGeoPoint::FromPoint2D (const GpPoint2d& aPoint) noexcept
{
    Set
    (
        geo_lat_t::SMake(aPoint.X()),
        geo_lon_t::SMake(aPoint.Y())
    );

    return *this;
}

constexpr GpGeoPoint    GpGeoPoint::SFromPoint2D (const GpPoint2d& aPoint) noexcept
{
    GpGeoPoint p;
    p.FromPoint2D(aPoint);
    return p;
}

}//namespace GPlatform
