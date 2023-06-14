#pragma once

#include "GpGeoPoint.hpp"
#include "../../../GpGeometry/GpGeometryCore/GpAabb2d.hpp"

namespace GPlatform {

class GpGeoShape;

class GP_GEO_CORE_API GpGeoAABB
{
public:
    CLASS_DD(GpGeoAABB)

    enum InitMode
    {
        ALL_SPHERE_WGS84
    };

    using IntersectLineRes = std::optional<std::tuple<GpGeoPoint, GpGeoPoint>>;

private:
    constexpr inline                    GpGeoAABB           (const GpAabb2d& aAABB) noexcept;

public:
    constexpr inline                    GpGeoAABB           (void) noexcept = default;
    constexpr inline                    GpGeoAABB           (const InitMode /*aInitMode*/) noexcept;
    constexpr inline                    GpGeoAABB           (const GpGeoAABB& aAABB) noexcept;
    constexpr inline                    GpGeoAABB           (GpGeoAABB&& aAABB) noexcept;

#if  (__cplusplus >= CPP_VERSION_20)
    constexpr                           ~GpGeoAABB          (void) noexcept = default;
#else
                                        ~GpGeoAABB          (void) noexcept = default;
#endif//#if  (__cplusplus >= CPP_VERSION_20)

    constexpr const GpAabb2d&           _InnerAABB          (void) const noexcept {return iAABB;}

    inline static GpGeoAABB             SFromCentralPoint   (const GpGeoPoint&  aCenter,
                                                             const geo_lat_t    aSizeLat,
                                                             const geo_lon_t    aSizeLon) noexcept;
    inline static GpGeoAABB             SFromPoint          (const GpGeoPoint&  aPointA) noexcept;
    inline static GpGeoAABB             SFromPoints         (const GpGeoPoint&  aPointA,
                                                             const GpGeoPoint&  aPointB) noexcept;
    inline static GpGeoAABB             SFromMinMax         (const GpGeoPoint&  aPointMin,
                                                             const GpGeoPoint&  aPointMax) noexcept;
    static GpGeoAABB                    SFromShape          (const GpGeoShape& aShape) noexcept;

    constexpr inline void               Reset               (void) noexcept;

    constexpr inline GpGeoAABB&         operator=           (const GpGeoAABB& aAABB) noexcept;
    constexpr inline GpGeoAABB&         operator=           (GpGeoAABB&& aAABB) noexcept;
    constexpr inline bool               operator==          (const GpGeoAABB& aAABB) const noexcept;

    inline const GpGeoPoint&            Min                 (void) const noexcept;
    inline const GpGeoPoint&            Max                 (void) const noexcept;
    inline const GpGeoPoint&            Center              (void) const noexcept;
    constexpr geo_lat_t                 HalfSizeLat         (void) const noexcept {return geo_lat_t::SMake(iAABB.HalfSizeX());}
    constexpr geo_lon_t                 HalfSizeLon         (void) const noexcept {return geo_lon_t::SMake(iAABB.HalfSizeY());}
    constexpr double                    Radius              (void) const noexcept {return iAABB.Radius();}

    constexpr inline GpGeoAABB&         Set                 (const GpGeoAABB& aAABB) noexcept;

    constexpr inline bool               IsEqual             (const GpGeoAABB& aAABB) const noexcept;
    constexpr inline bool               IsContain           (const GpGeoPoint& aPoint) const noexcept;
    constexpr inline bool               IsContain           (const geo_lat_t aLat,
                                                             const geo_lon_t aLon) const noexcept;
    constexpr inline bool               IsIntersect         (const GpGeoAABB& aAABB) const noexcept;
    inline IntersectLineRes             Intersect           (const GpGeoPoint& aPointA,
                                                             const GpGeoPoint& aPointB) const noexcept;

    inline std::optional<std::array<std::array<size_t, 2>, 2>>
                                        SpartialIdxIntersect(const GpGeoAABB&   aAABB,
                                                             const size_t       aSpartialResolution) const noexcept;

    static GpGeoAABB                    SFromPointAndR      (const GpGeoPoint&  aSearchPoint,
                                                             const meters_t     aSearchRadius);

    inline std::array<GpGeoPoint, 4>    ToPoints            (void) const noexcept;

private:
    GpAabb2d                            iAABB;
};

constexpr GpGeoAABB::GpGeoAABB (const GpAabb2d& aAABB) noexcept:
iAABB(aAABB)
{
}

constexpr GpGeoAABB::GpGeoAABB (const InitMode /*aInitMode*/) noexcept:
iAABB(GpAabb2d::SFromPoints
(
    {-90.0, -180.0},
    { 90.0,  180.0}
))
{
}

constexpr GpGeoAABB::GpGeoAABB (const GpGeoAABB& aAABB) noexcept:
iAABB(aAABB.iAABB)
{
}

constexpr GpGeoAABB::GpGeoAABB (GpGeoAABB&& aAABB) noexcept:
iAABB(std::move(aAABB.iAABB))
{
}

GpGeoAABB   GpGeoAABB::SFromCentralPoint
(
    const GpGeoPoint&   aCenter,
    const geo_lat_t     aSizeLat,
    const geo_lon_t     aSizeLon
) noexcept
{
    return GpAabb2d::SFromCentralPoint
    (
        reinterpret_cast<const GpPoint2d&>(aCenter),
        aSizeLat.Value(),
        aSizeLon.Value()
    );
}

GpGeoAABB   GpGeoAABB::SFromPoint (const GpGeoPoint& aPoint) noexcept
{
    return GpAabb2d::SFromPoint
    (
        reinterpret_cast<const GpPoint2d&>(aPoint)
    );
}

GpGeoAABB   GpGeoAABB::SFromPoints
(
    const GpGeoPoint&   aPointA,
    const GpGeoPoint&   aPointB
) noexcept
{
    return GpAabb2d::SFromPoints
    (
        reinterpret_cast<const GpPoint2d&>(aPointA),
        reinterpret_cast<const GpPoint2d&>(aPointB)
    );
}

GpGeoAABB   GpGeoAABB::SFromMinMax
(
    const GpGeoPoint&   aPointMin,
    const GpGeoPoint&   aPointMax
) noexcept
{
    return GpAabb2d::SFromMinMax
    (
        reinterpret_cast<const GpPoint2d&>(aPointMin),
        reinterpret_cast<const GpPoint2d&>(aPointMax)
    );
}

constexpr void  GpGeoAABB::Reset (void) noexcept
{
    iAABB.Reset();
}

constexpr GpGeoAABB&    GpGeoAABB::operator= (const GpGeoAABB& aAABB) noexcept
{
    iAABB = aAABB.iAABB;
    return *this;
}

constexpr GpGeoAABB&    GpGeoAABB::operator= (GpGeoAABB&& aAABB) noexcept
{
    iAABB = std::move(aAABB.iAABB);
    return *this;
}

constexpr bool  GpGeoAABB::operator== (const GpGeoAABB& aAABB) const noexcept
{
    return iAABB == aAABB.iAABB;
}

const GpGeoPoint&   GpGeoAABB::Min (void) const noexcept
{
    return reinterpret_cast<const GpGeoPoint&>(iAABB.Min());
}

const GpGeoPoint&   GpGeoAABB::Max (void) const noexcept
{
    return reinterpret_cast<const GpGeoPoint&>(iAABB.Max());
}

const GpGeoPoint&   GpGeoAABB::Center (void) const noexcept
{
    return reinterpret_cast<const GpGeoPoint&>(iAABB.Center());
}

constexpr GpGeoAABB&    GpGeoAABB::Set (const GpGeoAABB& aAABB) noexcept
{
    iAABB.Set(aAABB.iAABB);
    return *this;
}

constexpr bool  GpGeoAABB::IsEqual (const GpGeoAABB& aAABB) const noexcept
{
    return iAABB.IsEqual(aAABB.iAABB);
}

constexpr bool  GpGeoAABB::IsContain (const GpGeoPoint& aPoint) const noexcept
{
    return IsContain
    (
        aPoint.Lat(),
        aPoint.Lon()
    );
}

constexpr bool  GpGeoAABB::IsContain
(
    const geo_lat_t aLat,
    const geo_lon_t aLon
) const noexcept
{
    return iAABB.IsContain
    (
        aLat.Value(),
        aLon.Value()
    );
}

constexpr bool  GpGeoAABB::IsIntersect (const GpGeoAABB& aAABB) const noexcept
{
    return iAABB.IsIntersect(aAABB.iAABB);
}

GpGeoAABB::IntersectLineRes GpGeoAABB::Intersect
(
    const GpGeoPoint& aPointA,
    const GpGeoPoint& aPointB
) const noexcept
{
    const GeometryTypes::TrimLine2dResT res = iAABB.Trim
    (
        {reinterpret_cast<const GpPoint2d&>(aPointA),
         reinterpret_cast<const GpPoint2d&>(aPointB)}
    );

    if (res.has_value())
    {
        const GpLine2d& line = res.value();

        return std::tuple<GpGeoPoint, GpGeoPoint>
        {
            reinterpret_cast<const GpGeoPoint&>(line.Start()),
            reinterpret_cast<const GpGeoPoint&>(line.End())
        };
    } else
    {
        return std::nullopt;
    }   
}

std::optional<std::array<std::array<size_t, 2>, 2>> GpGeoAABB::SpartialIdxIntersect
(
    const GpGeoAABB&    aAABB,
    const size_t        aSpartialResolution
) const noexcept
{
    return iAABB.SpartialIdxIntersect(aAABB.iAABB, aSpartialResolution);
}

std::array<GpGeoPoint, 4>   GpGeoAABB::ToPoints (void) const noexcept
{
    const std::array<GpPoint2d, 4> points = iAABB.ToPoints();

    return
    {
        reinterpret_cast<const GpGeoPoint&>(points[0]),
        reinterpret_cast<const GpGeoPoint&>(points[1]),
        reinterpret_cast<const GpGeoPoint&>(points[2]),
        reinterpret_cast<const GpGeoPoint&>(points[3])
    };
}

}//namespace GPlatform
