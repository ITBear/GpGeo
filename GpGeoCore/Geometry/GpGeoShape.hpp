#pragma once

#include "GpGeoPolyline.hpp"
#include "GpGeoAABB.hpp"
#include "GpGeoShapeType.hpp"

namespace GPlatform {

class GP_GEO_CORE_API GpGeoShape
{
public:
    CLASS_DD(GpGeoShape)

public:
    using ContoursT = GpGeoPolyline::C::Vec::Val;

public:
    inline                  GpGeoShape      (void) noexcept;
    inline                  GpGeoShape      (const GpGeoShape& aShape);
    inline                  GpGeoShape      (GpGeoShape&& aShape) noexcept;
    inline                  GpGeoShape      (ContoursT aContours) noexcept;
                            ~GpGeoShape     (void) noexcept = default;

    inline GpGeoShape&      operator=       (const GpGeoShape& aShape);
    inline GpGeoShape&      operator=       (GpGeoShape&& aShape) noexcept;

    GpGeoShapeType::EnumT   Type            (void) const noexcept;

    const ContoursT&        Contours        (void) const noexcept {return iContours;}
    ContoursT&              Contours        (void) noexcept {return iContours;}

    inline GpGeoShape&      AddContour      (GpGeoPolyline aContour);

    GpGeoShape              Intersect       (const GpGeoAABB& aAABB) const;

private:
    ContoursT               iContours;
};

GpGeoShape::GpGeoShape (void) noexcept
{
}

GpGeoShape::GpGeoShape (const GpGeoShape& aShape):
iContours(aShape.iContours)
{
}

GpGeoShape::GpGeoShape (GpGeoShape&& aShape) noexcept:
iContours(std::move(aShape.iContours))
{
}

GpGeoShape::GpGeoShape (ContoursT aContours) noexcept:
iContours(std::move(aContours))
{
}

GpGeoShape& GpGeoShape::operator= (const GpGeoShape& aShape)
{
    iContours = aShape.iContours;
    return *this;
}

GpGeoShape& GpGeoShape::operator= (GpGeoShape&& aShape) noexcept
{
    iContours = std::move(aShape.iContours);
    return *this;
}

GpGeoShape& GpGeoShape::AddContour (GpGeoPolyline aContour)
{
    iContours.emplace_back(std::move(aContour));
    return *this;
}

}//namespace GPlatform
