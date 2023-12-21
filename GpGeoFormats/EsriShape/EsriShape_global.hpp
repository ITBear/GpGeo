#pragma once

#include <GpCore2/GpUtils/Macro/GpMacroImportExport.hpp>

#if defined(GP_GEO_FORMATS_ESRI_SHAPE_LIBRARY)
    #define GP_GEO_FORMATS_ESRI_SHAPE_API GP_DECL_EXPORT
#else
    #define GP_GEO_FORMATS_ESRI_SHAPE_API GP_DECL_IMPORT
#endif

namespace GPlatform {}

using namespace GPlatform;
