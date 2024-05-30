#include "GpGeoShapeCache.hpp"
#include "GpGeoShapeCacheImpl.hpp"

namespace GPlatform {

GpGeoShapeCache::GpGeoShapeCache (void):
iImpl(std::make_unique<GpGeoShapeCacheImpl>())
{   
}

GpGeoShapeCache::~GpGeoShapeCache (void) noexcept
{
}

}// namespace GPlatform
