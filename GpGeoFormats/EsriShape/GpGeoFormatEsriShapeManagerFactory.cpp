#include "GpGeoFormatEsriShapeManagerFactory.hpp"
#include "GpGeoFormatEsriShapeManager.hpp"

namespace GPlatform {

GpGeoFormatEsriShapeManagerFactory::~GpGeoFormatEsriShapeManagerFactory (void) noexcept
{
}

GpGeoFormatManager::SP  GpGeoFormatEsriShapeManagerFactory::NewInstance (void) const
{
    return MakeSP<GpGeoFormatEsriShapeManager>();
}

}// namespace GPlatform
