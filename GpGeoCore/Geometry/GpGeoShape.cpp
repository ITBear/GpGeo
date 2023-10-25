#include "GpGeoShape.hpp"
#include "GpGeoShapeCacheImpl.hpp"

namespace GPlatform {

GpGeoShapeType::EnumT   GpGeoShape::Type (void) const noexcept
{
    GpGeoShapeType::EnumT type = GpGeoShapeType::UNKNOWN;

    for (const GpGeoPolyline& contour: iContours)
    {
        const GpGeoPoint::C::Vec::Val& points = contour.Points();

        GpGeoShapeType::EnumT contourType = GpGeoShapeType::UNKNOWN;

        if (points.empty())
        {
            contourType = GpGeoShapeType::UNKNOWN;
        } else if (points.size() == 1)
        {
            contourType = GpGeoShapeType::POINTS;
        } else if (points[0] != points[points.size()-1])
        {
            contourType = GpGeoShapeType::LINES;
        } else //if (points[0] == points[points.size()-1])
        {
            contourType = GpGeoShapeType::POLYGONS;
        }

        if (type == GpGeoShapeType::UNKNOWN)
        {
            type = contourType;
        } else if (contourType != type)
        {
            type = GpGeoShapeType::MIXED;
            break;
        }
    }

    return type;
}

size_t  GpGeoShape::PointsCount (void) const noexcept
{
    size_t totalCount = 0;

    for (const GpGeoPolyline& contour: iContours)
    {
        totalCount += contour.PointsCount();
    }

    return totalCount;
}

GpGeoShape::PointsLatLonT   GpGeoShape::CollectPointsLatLon (void) const
{
    const size_t    pointsCount = PointsCount();
    PointsLatT      pointsLat;
    PointsLonT      pointsLon;

    pointsLat.resize(pointsCount);
    pointsLon.resize(pointsCount);

    size_t pointId      = 0;
    size_t contourId    = 0;

    std::vector<size_t> contoursSize;
    contoursSize.resize(iContours.size());

    for (const GpGeoPolyline& contour: iContours)
    {
        const GpGeoPoint::C::Vec::Val& contourPoints = contour.Points();

        contoursSize[contourId++] = contour.PointsCount();

        for (const GpGeoPoint& p: contourPoints)
        {
            pointsLat[pointId] = p.Lat();
            pointsLon[pointId] = p.Lon();
            pointId++;
        }
    }

    return PointsLatLonT
    {
        std::move(pointsLat),
        std::move(pointsLon),
        std::move(contoursSize)
    };
}

bool    GpGeoShape::IsInside (const GpGeoAABB& aAABB) const
{
    for (const GpGeoPolyline& contour: iContours)
    {
        const GpGeoPoint::C::Vec::Val& points = contour.Points();

        for (const GpGeoPoint& point: points)
        {
            if (aAABB.IsContain(point) == false)
            {
                return false;
            }
        }
    }

    return true;
}

GpGeoShape::C::Vec::Val GpGeoShape::Intersect
(
    const GpGeoAABB& aAABB,
    GpGeoShapeCache& aCache
) const
{
    GpGeoShapeType::EnumT shapeType = Type();

    switch (shapeType)
    {
        case GpGeoShapeType::POINTS:    return {_IntersectPoints(aAABB)};
        case GpGeoShapeType::LINES:     return {_IntersectLines(aAABB, aCache)};
        case GpGeoShapeType::POLYGONS:  return _IntersectPolygons(aAABB, aCache);
        case GpGeoShapeType::MIXED:     THROW_GP(u8"Unsupported shape type GpGeoShapeType::MIXED"_sv);
        case GpGeoShapeType::UNKNOWN: [[fallthrough]];
        default:                        THROW_GP(u8"Unknown shape type"_sv);
    }

    return {};
}

GpGeoShape  GpGeoShape::_IntersectPoints (const GpGeoAABB& aAABB) const
{
    GpGeoShape resShape;

    for (const GpGeoPolyline& contour: iContours)
    {
        GpGeoPolyline                   newContour;
        GpGeoPoint::C::Vec::Val&        newPoints   = newContour.Points();
        const GpGeoPoint::C::Vec::Val&  points      = contour.Points();

        for (const GpGeoPoint& point: points)
        {
            if (aAABB.IsContain(point) == false)
            {
                newPoints.emplace_back(point);
            }
        }

        if (newContour.PointsCount() > 0)
        {
            resShape.AddContour(std::move(newContour));
        }
    }

    return resShape;
}

GpGeoShape  GpGeoShape::_IntersectLines
(
    const GpGeoAABB& aAABB,
    GpGeoShapeCache& /*aCache*/
) const
{
    const Boost_BoxT aabb =
    {
        reinterpret_cast<const Boost_PointT&>(aAABB.Min()),
        reinterpret_cast<const Boost_PointT&>(aAABB.Max())
    };

    GpGeoShape                  resShape;
    GpGeoPolyline::C::Vec::Val& resContours = resShape.Contours();

    const size_t contoursCount = iContours.size();

    for (size_t contourId = 0; contourId < contoursCount; contourId++)
    {
        Boost_LinestringT                   polyline;
        const GpGeoPolyline&                contour = iContours[contourId];
        const std::vector<Boost_PointT>&    points  = reinterpret_cast<const std::vector<Boost_PointT>&>(contour.Points());

        boost::geometry::append(polyline, points);
        boost::geometry::correct(polyline);

        std::vector<Boost_LinestringT> resPolylines;
        if (boost::geometry::intersection(polyline, aabb, resPolylines))
        {
            resContours.reserve(resContours.size() + resPolylines.size());

            for (const Boost_LinestringT& resLine: resPolylines)
            {
                resContours.emplace_back(GpGeoPolyline(reinterpret_cast<const GpGeoPoint::C::Vec::Val&>(resLine)));
            }
        }
    }   

    return resShape;
}

GpGeoShape::C::Vec::Val GpGeoShape::_IntersectPolygons
(
    const GpGeoAABB& aAABB,
    GpGeoShapeCache& aCache
) const
{
    const Boost_BoxT aabb =
    {
        reinterpret_cast<const Boost_PointT&>(aAABB.Min()),
        reinterpret_cast<const Boost_PointT&>(aAABB.Max())
    };

    if (aCache.Impl().iIsFill == false)
    {
        const size_t contoursCount = iContours.size();

        for (size_t contourId = 0; contourId < contoursCount; contourId++)
        {
            const GpGeoPolyline& contour = iContours[contourId];

            const std::vector<Boost_PointT>& points = reinterpret_cast<const std::vector<Boost_PointT>&>(contour.Points());

            if (contourId == 0)
            {
                boost::geometry::append(aCache.Impl().iPolygon, points);
            } else
            {
                aCache.Impl().iPolygon.inners().emplace_back(reinterpret_cast<const Boost_PolygonT::ring_type&>(points));
            }

            boost::geometry::correct(aCache.Impl().iPolygon);
        }

        aCache.Impl().iIsFill = true;
    }

    std::deque<Boost_PolygonT> resPolygons;
    if (boost::geometry::intersection(aCache.Impl().iPolygon, aabb, resPolygons))
    {
        GpGeoShape::C::Vec::Val resShapes;
        resShapes.resize(resPolygons.size());
        size_t resShapeId = 0;

        for (const Boost_PolygonT& resPolygon: resPolygons)
        {
            GpGeoShape&                 resShape    = resShapes[resShapeId++];
            GpGeoPolyline::C::Vec::Val& resContours = resShape.Contours();
            resContours.resize(1/*outer*/ + resPolygon.inners().size());

            size_t contourId = 0;

            resContours[contourId++] = reinterpret_cast<const GpGeoPoint::C::Vec::Val&>(resPolygon.outer());

            for (const auto& inner: resPolygon.inners())
            {
                resContours[contourId++] = reinterpret_cast<const GpGeoPoint::C::Vec::Val&>(inner);
            }
        }

        return resShapes;
    } else
    {
        return {};
    }
}

}//namespace GPlatform
