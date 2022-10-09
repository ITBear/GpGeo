#pragma once

#include "../../GpCore2/GpUtils/GpUtils.hpp"
#include "../../GpGeometry/GpGeometryCore/GpGeometryCore.hpp"

using namespace GPlatform;

#if defined(GP_GEO_CORE_LIBRARY)
    #define GP_GEO_CORE_API GP_DECL_EXPORT
#else
    #define GP_GEO_CORE_API GP_DECL_IMPORT
#endif
