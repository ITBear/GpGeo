#include <GpGeo/GpGeoFormats/EsriShape/GpGeoFormatEsriShapeManagerFactory.hpp>
#include <GpGeo/GpGeoFormats/EsriShape/GpGeoFormatEsriShapeManager.hpp>

namespace GPlatform {

GpGeoFormatEsriShapeManagerFactory::~GpGeoFormatEsriShapeManagerFactory (void) noexcept
{
}

GpGeoFormatManager::SP  GpGeoFormatEsriShapeManagerFactory::NewInstance (void) const
{
    return MakeSP<GpGeoFormatEsriShapeManager>();
}

}// namespace GPlatform
