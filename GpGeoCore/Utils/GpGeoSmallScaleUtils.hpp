#pragma once

#include "../Geometry/GpGeoGeometry.hpp"

namespace GPlatform {

class GP_GEO_CORE_API GpGeoSmallScaleUtils
{
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoSmallScaleUtils)

public:
    struct NearestPointRes
    {
        GpGeoPoint  point;
        size_t      segmentId       = 0;
        double      distanceSquare  = 0.0;
    };

    struct NearestPointContourRes
    {
        GpGeoPoint  point;
        size_t      segmentId       = 0;
        size_t      contourId       = 0;
        double      distanceSquare  = 0.0;
    };

public:
    inline static constexpr double          SDistance       (const GpGeoPoint&  aPointA,
                                                             const GpGeoPoint&  aPointB) noexcept;
    inline static constexpr double          SDistanceSquare (const GpGeoPoint&  aPointA,
                                                             const GpGeoPoint&  aPointB) noexcept;

    inline static GpGeoPoint                SNearestPoint   (const GpGeoPoint&  aPoint,
                                                             const GpGeoPoint&  aSegmentPointA,
                                                             const GpGeoPoint&  aSegmentPointB);
    inline static NearestPointRes           SNearestPoint   (const GpGeoPoint&      aPoint,
                                                             const GpGeoPolyline&   aPolyline);
    inline static NearestPointContourRes    SNearestPoint   (const GpGeoPoint&                  aPoint,
                                                             const GpGeoPolyline::C::Vec::Val&  aContours);
};

constexpr double    GpGeoSmallScaleUtils::SDistance
(
    const GpGeoPoint&   aPointA,
    const GpGeoPoint&   aPointB
) noexcept
{
    return GpGeometryAlgo2d::SDistance
    (
        aPointA.AsPoint2D(),
        aPointB.AsPoint2D()
    );
}

constexpr double    GpGeoSmallScaleUtils::SDistanceSquare
(
    const GpGeoPoint&   aPointA,
    const GpGeoPoint&   aPointB
) noexcept
{
    return GpGeometryAlgo2d::SDistanceSquare
    (
        aPointA.AsPoint2D(),
        aPointB.AsPoint2D()
    );
}

GpGeoPoint  GpGeoSmallScaleUtils::SNearestPoint
(
    const GpGeoPoint&   aPoint,
    const GpGeoPoint&   aSegmentPointA,
    const GpGeoPoint&   aSegmentPointB
)
{
    return GpGeoPoint::SFromPoint2D(GpGeometryAlgo2d::SNearestPoint
    (
        aPoint.AsPoint2D(),
        aSegmentPointA.AsPoint2D(),
        aSegmentPointB.AsPoint2D()
    ));
}

GpGeoSmallScaleUtils::NearestPointRes   GpGeoSmallScaleUtils::SNearestPoint
(
    const GpGeoPoint&       aPoint,
    const GpGeoPolyline&    aPolyline
)
{
    const GpGeoPoint::C::Vec::Val&  points      = aPolyline.Points();
    const size_t                    pointsCount = std::size(points);

    THROW_COND_GP
    (
        pointsCount > 0,
        "Points count is zero"_sv
    );

    if (pointsCount == 1)
    {
        return NearestPointRes
        {
            .point          = points[0],
            .segmentId      = 0,
            .distanceSquare = SDistanceSquare(aPoint, points[0])
        };
    }

    double      minDistanceSquare   = std::numeric_limits<double>::max();
    GpGeoPoint  nearestPoint        = points[0];
    size_t      segmentId           = 0;

    for (size_t pointId = 1; pointId < pointsCount; pointId++)
    {
        const GpGeoPoint currentNearestPoint = SNearestPoint
        (
            aPoint,
            points[pointId - 1],
            points[pointId]
        );

        const double currentDistanceSquare = SDistanceSquare(aPoint, currentNearestPoint);
        if (currentDistanceSquare < minDistanceSquare)
        {
            minDistanceSquare   = currentDistanceSquare;
            nearestPoint        = currentNearestPoint;
            segmentId           = pointId - 1;
        }
    }

    return NearestPointRes
    {
        .point          = nearestPoint,
        .segmentId      = segmentId,
        .distanceSquare = minDistanceSquare
    };
}

GpGeoSmallScaleUtils::NearestPointContourRes    GpGeoSmallScaleUtils::SNearestPoint
(
    const GpGeoPoint&                   aPoint,
    const GpGeoPolyline::C::Vec::Val&   aContours
)
{
    NearestPointContourRes  res;
    size_t                  contourId = 0;

    res.distanceSquare = std::numeric_limits<double>::max();

    for (const GpGeoPolyline& polyline: aContours)
    {
        const NearestPointRes currentRes = SNearestPoint(aPoint, polyline);

        if (currentRes.distanceSquare < res.distanceSquare)
        {
            res.point           = currentRes.point;
            res.segmentId       = currentRes.segmentId;
            res.contourId       = contourId;
            res.distanceSquare  = currentRes.distanceSquare;
        }

        contourId++;
    }

    return res;
}

}// namespace GPlatform
