#include "GpGeoShape.hpp"

namespace GPlatform {

GpGeoShapeType::EnumT   GpGeoShape::Type (void) const noexcept
{
    if (iContours.size() == 0)
    {
        return GpGeoShapeType::UNKNOWN;
    }

    GpGeoShapeType::EnumT type = GpGeoShapeType::UNKNOWN;

    for (const GpGeoPolyline& contour: iContours)
    {
        const GpGeoPoint::C::Vec::Val& points = contour.Points();

        GpGeoShapeType::EnumT contourType = GpGeoShapeType::UNKNOWN;

        if (points.size() == 0)
        {
            contourType = GpGeoShapeType::UNKNOWN;
        } else if (points.size() == 1)
        {
            contourType = GpGeoShapeType::POINTS;
        } else if (points[0] != points[points.size()-1])
        {
            contourType = GpGeoShapeType::LINES;
        } else
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

GpGeoShape  GpGeoShape::Intersect (const GpGeoAABB& aAABB) const
{
    if (GpGlobals::S().Get("_SplitAndGroupByGeohash").has_value())
    {
        int d = 0;
    }

    const size_t    contoursCount   = iContours.size();
    ContoursT       resContours;
    resContours.reserve(contoursCount + 1);

    for (size_t contourId = 0; contourId < contoursCount; contourId++)
    {
        //Get element
        const GpGeoPolyline& contour = iContours[contourId];

        //Do intersect
        GpGeoPolyline::IntersectResT contourIntersectRes = contour.Intersect(aAABB);

        //Check res
        if (std::holds_alternative<GpGeoPolyline::IntersectStateT>(contourIntersectRes))//All element are keept or dropped by filter
        {
            const auto intersectState = std::get<GpGeoPolyline::IntersectStateT>(contourIntersectRes);

            if (intersectState == GpGeoPolyline::IntersectStateT::ALL_KEEPT)
            {
                resContours.emplace_back(contour);
            }
        } else if (std::holds_alternative<GpGeoPolyline::C::Vec::Val>(contourIntersectRes))
        {
            GpGeoPolyline::C::Vec::Val& intersectContours = std::get<GpGeoPolyline::C::Vec::Val>(contourIntersectRes);

            resContours.insert
            (
                resContours.end(),
                std::make_move_iterator(intersectContours.begin()),
                std::make_move_iterator(intersectContours.end())
            );
        } else
        {
            THROW_GP("Wrong variant state"_sv);
        }
    }

    return resContours;
}

}//namespace GPlatform
