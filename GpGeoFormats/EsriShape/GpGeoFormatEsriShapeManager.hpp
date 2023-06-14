#pragma once

#include "EsriShape_global.hpp"
#include "../../GpGeoCore/Utils/GpGeoFormatManager.hpp"
#include <shapelib/shapefil.h>

namespace GPlatform {

class GpGeoFormatEsriShapeManager final: public GpGeoFormatManager
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpGeoFormatEsriShapeManager)
    CLASS_DD(GpGeoFormatEsriShapeManager)

public:
                                    GpGeoFormatEsriShapeManager     (void) = default;
    virtual                         ~GpGeoFormatEsriShapeManager    (void) noexcept override final;

    virtual GpGeoShape::C::Vec::Val Read                            (std::u8string_view aFileName) override final;
    virtual void                    Write                           (const GpGeoShape::C::Vec::Val& aShapes,
                                                                     std::u8string_view             aFileName) override final;

private:
    GpGeoShape                      ReadShape                       (SHPObject* aShapeObj) const;
};

}//namespace  GPlatform
