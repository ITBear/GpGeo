#pragma once

#include "../GpGeoCore_global.hpp"
#include <memory>

namespace GPlatform {

class GpGeoShapeCacheImpl;

class GP_GEO_CORE_API GpGeoShapeCache
{
public:
                                            GpGeoShapeCache     (void);
                                            ~GpGeoShapeCache    (void) noexcept;

    GpGeoShapeCacheImpl&                    Impl                (void) {return *iImpl.get();}

private:
    std::unique_ptr<GpGeoShapeCacheImpl>    iImpl;
};

}// namespace GPlatform
