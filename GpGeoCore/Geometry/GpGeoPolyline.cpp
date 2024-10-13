#include <GpGeo/GpGeoCore/Geometry/GpGeoPolyline.hpp>
#include <GpGeo/GpGeoCore/Geometry/GpGeoAABB.hpp>
#include <GpGeometry/GpGeometryCore/Algorithms/GpGeometryIntersectAlgo2d.hpp>

namespace GPlatform {

GpGeoPolyline   GpGeoPolyline::SFrom2DPoints (const GpPoint2d::C::Vec::Val& aPoints)
{
    GpGeoPoint::C::Vec::Val geopoints;
    geopoints.reserve(std::size(aPoints));

    for (const GpPoint2d& p: aPoints)
    {
        geopoints.emplace_back(reinterpret_cast<const GpGeoPoint&>(p));
    }

    return GpGeoPolyline(std::move(geopoints));
}

/*GpGeoPolyline::TrimResT       GpGeoPolyline::STrim
(
    const GpGeoPolyline&    aPolyline,
    const GpGeoAABB&        aAABB
)
{
    const PointsT&  points      = aPolyline.Points();
    const size_t    pointsCount = std::size(points);

    if (pointsCount == 0)
    {
        return TrimStateT::ALL_DROPPED;
    }

    if (pointsCount == 1)
    {
        return aAABB.IsContain(points[0]) ?
              TrimStateT::ALL_KEEPT
            : TrimStateT::ALL_DROPPED;
    }

    if (points[0] != points[pointsCount-1])//polyline
    {
        return _STrimPolyline(aPolyline, aAABB);
    } else//polyline
    {
        return _STrimPolygon(aPolyline, aAABB);
    }
}*/

/*GpGeoPolyline::TrimResT   GpGeoPolyline::_STrimPolyline
(
    const GpGeoPolyline&    aPolyline,
    const GpGeoAABB&        aAABB
)
{
    const PointsT&  points      = aPolyline.Points();
    const size_t    pointsCount = std::size(points);

    if (pointsCount == 0)
    {
        return TrimStateT::ALL_DROPPED;
    }

    GpGeoPoint prevPoint = points[0];

    if (pointsCount == 1)
    {
        return aAABB.IsContain(prevPoint) ? TrimStateT::ALL_KEEPT : TrimStateT::ALL_DROPPED;
    }

    GpGeoPolyline::C::Vec::Val* polylines       = nullptr;
    TrimResT                    res             = TrimStateT::ALL_DROPPED;
    GpGeoPoint                  startPoint      = prevPoint;
    ssize_t                     startPointId    = 0;

    for (size_t pointId = 1; pointId < pointsCount; pointId++)
    {
        const GpGeoPoint                    currentPoint = points[pointId];
        const GpGeoAABB::IntersectLineRes   intersectRes = aAABB.Intersect(prevPoint, currentPoint);

        if (intersectRes.has_value())//Inside or intersected
        {
            const auto& intersectResVal = intersectRes.value();
            const GpGeoPoint pointA = std::get<0>(intersectResVal);
            const GpGeoPoint pointB = std::get<1>(intersectResVal);

            if (   (   prevPoint != pointA)
                && (currentPoint == pointB))//Intersected (out->in)
            {
                startPointId    = ssize_t(pointId) - 1;
                startPoint      = pointA;
            } else if (   (   prevPoint == pointA)
                       && (currentPoint != pointB))//Intersected (in->out)
            {
                if (polylines == nullptr)
                {
                    res = GpGeoPolyline::C::Vec::Val();
                    polylines = &(std::get<GpGeoPolyline::C::Vec::Val>(res));
                }

                polylines->emplace_back(SFromSubPolyline
                (
                    points,
                    size_t(startPointId),
                    startPoint,
                    pointId,
                    pointB
                ));

                startPointId = -1;
            } else if (   (   prevPoint != pointA)
                       && (currentPoint != pointB))//Intersected (out->in->out)
            {
                if (polylines == nullptr)
                {
                    res = GpGeoPolyline::C::Vec::Val();
                    polylines = &(std::get<GpGeoPolyline::C::Vec::Val>(res));
                }

                polylines->emplace_back(SFromSubPolyline
                (
                    points,
                    0,
                    pointA,
                    1,
                    pointB
                ));

                startPointId = -1;
            } else//Inside
            {
                //NOP
            }
        } else//Outside
        {
            startPointId = -1;
        }

        prevPoint = currentPoint;
    }

    if (startPointId > -1)
    {
        if (polylines == nullptr)
        {
            res = GpGeoPolyline::C::Vec::Val();
            polylines = &(std::get<GpGeoPolyline::C::Vec::Val>(res));
        }

        polylines->emplace_back(SFromSubPolyline
        (
            points,
            size_t(startPointId),
            startPoint,
            pointsCount - 1,
            points[pointsCount - 1]
        ));
    } else if (std::holds_alternative<TrimStateT>(res))
    {
        if (startPointId == -1)
        {
            res = TrimStateT::ALL_DROPPED;
        } else
        {
            res = TrimStateT::ALL_KEEPT;
        }
    }

    return res;
}*/

/*GpGeoPolyline::TrimResT   GpGeoPolyline::_STrimPolygon
(
    const GpGeoPolyline&    aPolyline,
    const GpGeoAABB&        aAABB
)
{
    const PointsT&  points      = aPolyline.Points();
    const size_t    pointsCount = std::size(points);

    if (pointsCount == 0)
    {
        return TrimStateT::ALL_DROPPED;
    }

    GpGeoPoint prevPoint = points[0];

    if (pointsCount == 1)
    {
        return aAABB.IsContain(prevPoint) ? TrimStateT::ALL_KEEPT : TrimStateT::ALL_DROPPED;
    }

    //Geo polygon to polygon
    GpPolyline2d polygon;
    {
        std::vector<GpPoint2d>& polygonPoints = polygon.Points();
        polygonPoints.resize(pointsCount);

        for (size_t id = 0; id < pointsCount; id++)
        {
            const GpGeoPoint& geoPoint = points[id];
            polygonPoints[id].SetX(geoPoint.Lat().Value());
            polygonPoints[id].SetY(geoPoint.Lon().Value());
        }
    }

    if (aAABB._InnerAABB().IsContain(polygon))
    {
        return TrimStateT::ALL_KEEPT;
    }

    GpPolyline2d::C::Vec::Val resPolygons = GpGeometryIntersectAlgo2d::STrimByAabb(polygon, aAABB._InnerAABB());

    if (resPolygons.empty())
    {
        return TrimStateT::ALL_DROPPED;
    }

    //Polygons to Geo polygons
    GpGeoPolyline::C::Vec::Val geoPolygons;
    {
        for (const GpPolyline2d& p: resPolygons)
        {
            const std::vector<GpPoint2d>&   _points         = p.Points();
            const size_t                    _pointsCount    = std::size(_points);

            GpGeoPolyline gp;
            GpGeoPoint::C::Vec::Val&        gpPoints    = gp.Points();
            gpPoints.resize(_pointsCount);

            for (size_t pointId = 0; pointId < _pointsCount; pointId++)
            {
                const GpPoint2d& point = _points[pointId];

                gpPoints[pointId].Set
                (
                    geo_lat_t::SMake(point.X()),
                    geo_lon_t::SMake(point.Y())
                );
            }

            geoPolygons.emplace_back(std::move(gp));
        }
    }

    return geoPolygons;
}
*/
/*GpGeoPolyline GpGeoPolyline::SFromSubPolyline
(
    const PointsT&      aPoints,
    const size_t        aStartPointId,
    const GpGeoPoint&   aStartPoint,
    const size_t        aEndPointId,
    const GpGeoPoint&   aEndPoint
)
{
    GpGeoPolyline   polilineRes;
    PointsT&        points = polilineRes.Points();

    points.reserve(aEndPointId - aStartPointId + 1);

    points.emplace_back(aStartPoint);

    for (size_t id = aStartPointId + 1; id < aEndPointId; id++)
    {
        points.emplace_back(aPoints[id]);
    }

    points.emplace_back(aEndPoint);

    return polilineRes;
}*/

/*bool  GpGeoPolyline::SIsIntersect
(
    const GpGeoPolyline&    aContour,
    const GpGeoAABB&        aAABB
)
{
    const std::array<GpGeoPoint, 4> aabbPoints          = aAABB.ToPoints();
    const GpGeoPoint::C::Vec::Val&  polygonPoints       = aContour.Points();
    const size_t                    polygonPointsCount  = std::size(polygonPoints);

    // Test axes of the polygon
    for (size_t pointId = 0; i < polygonPointsCount; pointId++)
    {
        const GpGeoPoint&   pointA  = polygon[pointId];
        const GpGeoPoint&   pointB  = polygon[(pointId + 1) % polygonPointsCount];
        const GpGeoPoint    edge    = pointB - pointA;
        const GpGeoPoint    axis    = GpGeoPoint(geo_lat_t::SMake(-edge.Lon().Value()), geo_lon_t::SMake(edge.Lat()));

        double minA, maxA, minB, maxB;
        projectPolygon(polygon, axis, minA, maxA);
        projectPolygon(aabbPoints, axis, minB, maxB);

        if (!rangesOverlap(minA, maxA, minB, maxB))
        {
            return false;
        }
    }

    // Test axes of the AABB
    for (size_t pointId = 0; pointId < std::size(aabbPoints); pointId++)
    {
        const GpGeoPoint&   pointA  = aabbPoints[pointId];
        const GpGeoPoint&   pointB  = aabbPoints[(pointId + 1) % std::size(aabbPoints)];
        const GpGeoPoint    edge    = pointB - pointA;
        const GpGeoPoint    axis    = GpGeoPoint(geo_lat_t::SMake(-edge.Lon().Value()), geo_lon_t::SMake(edge.Lat()));

        double minA, maxA, minB, maxB;
        projectPolygon(polygon, axis, minA, maxA);
        projectPolygon(aabbPoints, axis, minB, maxB);

        if (!rangesOverlap(minA, maxA, minB, maxB))
        {
            return false;
        }
    }

    return true;
*/

}// namespace GPlatform
