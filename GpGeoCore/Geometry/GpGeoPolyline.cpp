#include "GpGeoPolyline.hpp"
#include "GpGeoAABB.hpp"

namespace GPlatform {

GpGeoPolyline   GpGeoPolyline::SFrom2DPoints (const GpPoint2d::C::Vec::Val& aPoints)
{
    GpGeoPoint::C::Vec::Val geopoints;
    geopoints.reserve(aPoints.size());

    for (const GpPoint2d& p: aPoints)
    {
        geopoints.emplace_back(reinterpret_cast<const GpGeoPoint&>(p));
    }

    return GpGeoPolyline(std::move(geopoints));
}

GpGeoPolyline::IntersectResT    GpGeoPolyline::Intersect (const GpGeoAABB& aAABB) const
{
    if (GpGlobals::S().Get("_SplitAndGroupByGeohash").has_value())
    {
        int d = 0;
    }

    const size_t pointsCount = iPoints.size();

    if (pointsCount == 0)
    {
        return IntersectStateT::ALL_DROPPED;
    }

    if (pointsCount == 1)
    {
        return aAABB.IsContain(iPoints[0]) ?
              IntersectStateT::ALL_KEEPT
            : IntersectStateT::ALL_DROPPED;
    }

    if (iPoints[0] != iPoints[pointsCount-1])//polyline
    {
        return _IntersectPolyline(aAABB);
    } else//polyline
    {
        return _IntersectPolygon(aAABB);
    }
}

GpGeoPolyline::IntersectResT    GpGeoPolyline::_IntersectPolyline (const GpGeoAABB& aAABB) const
{
    const size_t pointsCount = iPoints.size();

    if (pointsCount == 0)
    {
        return IntersectStateT::ALL_DROPPED;
    }

    GpGeoPoint prevPoint = iPoints[0];

    if (pointsCount == 1)
    {
        return aAABB.IsContain(prevPoint) ? IntersectStateT::ALL_KEEPT : IntersectStateT::ALL_DROPPED;
    }

    GpGeoPolyline::C::Vec::Val* polylines       = nullptr;
    IntersectResT               res             = IntersectStateT::ALL_DROPPED;
    GpGeoPoint                  startPoint      = prevPoint;
    ssize_t                     startPointId    = 0;

    for (size_t pointId = 1; pointId < pointsCount; pointId++)
    {
        if (   (pointId == 24)
            && (GpGlobals::S().Get("_SplitAndGroupByGeohash").has_value()))
        {
            int d = 0;
        }

        const GpGeoPoint                    currentPoint = iPoints[pointId];
        const GpGeoAABB::IntersectLineRes   intersectRes = aAABB.Intersect(prevPoint, currentPoint);

        if (intersectRes.has_value())//Inside or intersected
        {
            const auto& intersectResVal = intersectRes.value();
            const GpGeoPoint pointA = std::get<0>(intersectResVal);
            const GpGeoPoint pointB = std::get<1>(intersectResVal);

            if (   (   prevPoint != pointA)
                && (currentPoint == pointB))//Intersected (out->in)
            {
                startPointId    = pointId - 1;
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
                    iPoints,
                    startPointId,
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
                    iPoints,
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
            iPoints,
            startPointId,
            startPoint,
            iPoints.size() - 1,
            iPoints[iPoints.size() - 1]
        ));
    } else if (std::holds_alternative<IntersectStateT>(res))
    {
        if (startPointId == -1)
        {
            res = IntersectStateT::ALL_DROPPED;
        } else
        {
            res = IntersectStateT::ALL_KEEPT;
        }
    }

    return res;
}

GpGeoPolyline::IntersectResT    GpGeoPolyline::_IntersectPolygon (const GpGeoAABB& aAABB) const
{
    //TODO: implement
    //THROW_GP_NOT_IMPLEMENTED();
    return IntersectStateT::ALL_DROPPED;
}

GpGeoPolyline   GpGeoPolyline::SFromSubPolyline
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
}

}//namespace GPlatform
