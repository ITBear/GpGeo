#pragma once

#include "GpGeoPoint.hpp"

namespace GPlatform {

class GpGeoAABB;

class GP_GEO_CORE_API GpGeoPolyline
{
public:
    CLASS_DD(GpGeoPolyline)

public:
    enum class IntersectStateT
    {
        ALL_DROPPED,
        ALL_KEEPT
    };

    using PointsT       = GpGeoPoint::C::Vec::Val;
    using IntersectResT = std::variant<IntersectStateT, GpGeoPolyline::C::Vec::Val>;

public:
    inline                  GpGeoPolyline       (void) noexcept = default;
    inline                  GpGeoPolyline       (const GpGeoPolyline& aContour);
    inline                  GpGeoPolyline       (GpGeoPolyline&& aContour) noexcept;
    inline                  GpGeoPolyline       (GpGeoPoint::C::Vec::Val aPoints) noexcept;
                            ~GpGeoPolyline      (void) noexcept = default;

    static GpGeoPolyline    SFrom2DPoints       (const GpPoint2d::C::Vec::Val& aPoints);

    inline GpGeoPolyline&   operator=           (const GpGeoPolyline& aContour);
    inline GpGeoPolyline&   operator=           (GpGeoPolyline&& aContour) noexcept;

    const PointsT&          Points              (void) const noexcept {return iPoints;}
    PointsT&                Points              (void) noexcept {return iPoints;}

    IntersectResT           Intersect           (const GpGeoAABB& aAABB) const;

private:
    IntersectResT           _IntersectPolyline  (const GpGeoAABB& aAABB) const;
    IntersectResT           _IntersectPolygon   (const GpGeoAABB& aAABB) const;
    static GpGeoPolyline    SFromSubPolyline    (const PointsT&     aPoints,
                                                 const size_t       aStartPointId,
                                                 const GpGeoPoint&  aStartPoint,
                                                 const size_t       aEndPointId,
                                                 const GpGeoPoint&  aEndPoint);

private:
    PointsT                 iPoints;
};

GpGeoPolyline::GpGeoPolyline (const GpGeoPolyline& aContour):
iPoints(aContour.iPoints)
{
}

GpGeoPolyline::GpGeoPolyline (GpGeoPolyline&& aContour) noexcept:
iPoints(std::move(aContour.iPoints))
{
}

GpGeoPolyline::GpGeoPolyline (GpGeoPoint::C::Vec::Val aPoints) noexcept:
iPoints(std::move(aPoints))
{
}

GpGeoPolyline&  GpGeoPolyline::operator= (const GpGeoPolyline& aContour)
{
    iPoints = aContour.iPoints;
    return *this;
}

GpGeoPolyline&  GpGeoPolyline::operator= (GpGeoPolyline&& aContour) noexcept
{
    iPoints = std::move(aContour.iPoints);
    return *this;
}

}//namespace GPlatform
