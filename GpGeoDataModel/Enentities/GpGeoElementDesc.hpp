#pragma once

#include "../GpGeoDataModel_global.hpp"

namespace GPlatform {

class GP_GEO_DATA_MODEL_API GpGeoElementDesc final: public GpReflectObject
{
public:
    CLASS_DD(GpGeoElementDesc)
    REFLECT_DECLARE("d767d127-5e8d-4359-593c-e177fc510fac"_uuid)

public:
                        GpGeoElementDesc        (void) noexcept;
                        GpGeoElementDesc        (const GpGeoElementDesc& aDesc);
                        GpGeoElementDesc        (GpGeoElementDesc&& aDesc) noexcept;
    virtual             ~GpGeoElementDesc       (void) noexcept override final;

public:
    GpUUID              id;
    GpUUID              type_id;
    unix_ts_s_t         create_ts;
    unix_ts_s_t         update_ts;
    GpUUID              parent_id;
    s_int_64            shape_id = 0;
};

}//namespace GPlatform
