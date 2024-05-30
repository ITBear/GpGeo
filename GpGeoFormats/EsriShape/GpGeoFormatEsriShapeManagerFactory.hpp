#pragma once

#include "EsriShape_global.hpp"
#include "../../GpGeoCore/Utils/GpGeoFormatManagerFactory.hpp"

namespace GPlatform {

class GP_GEO_FORMATS_ESRI_SHAPE_API GpGeoFormatEsriShapeManagerFactory final: public GpGeoFormatManagerFactory
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpGeoFormatEsriShapeManagerFactory)
    CLASS_DD(GpGeoFormatEsriShapeManagerFactory)

public:
                                    GpGeoFormatEsriShapeManagerFactory  (void) = default;
    virtual                         ~GpGeoFormatEsriShapeManagerFactory (void) noexcept override final;

    virtual GpGeoFormatManager::SP  NewInstance                         (void) const override final;
};

}// namespace  GPlatform
