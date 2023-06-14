#pragma once

#include "../../GpCore2/GpUtils/Macro/GpMacroImportExport.hpp"

#if defined(GP_GEO_DATA_MODEL_LIBRARY)
    #define GP_GEO_DATA_MODEL_API GP_DECL_EXPORT
#else
    #define GP_GEO_DATA_MODEL_API GP_DECL_IMPORT
#endif

namespace GPlatform {}

using namespace GPlatform;
