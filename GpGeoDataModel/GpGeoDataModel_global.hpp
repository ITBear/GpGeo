#pragma once

#include "../../GpCore2/GpReflection/GpReflection.hpp"
#include "../GpGeoCore/GpGeoCore.hpp"

#if defined(GP_GEO_DATA_MODEL_LIBRARY)
    #define GP_GEO_DATA_MODEL_API GP_DECL_EXPORT
#else
    #define GP_GEO_DATA_MODEL_API GP_DECL_IMPORT
#endif

using namespace GPlatform;
