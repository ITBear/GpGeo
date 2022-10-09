#pragma once

#include "../GpGeoDataModel_global.hpp"

namespace GPlatform {

class GP_GEO_DATA_MODEL_API GpGeoElementNameDesc final: public GpReflectObject
{
public:
    CLASS_DD(GpGeoElementNameDesc)
    REFLECT_DECLARE("aa18b505-27d2-450d-cb44-9021becc25ae"_uuid)

public:
                        GpGeoElementNameDesc        (void) noexcept;
                        GpGeoElementNameDesc        (const GpGeoElementNameDesc& aDesc);
                        GpGeoElementNameDesc        (GpGeoElementNameDesc&& aDesc) noexcept;
    virtual             ~GpGeoElementNameDesc       (void) noexcept override final;

public:
    GpUUID              id;
    s_int_32            language_id;
    unix_ts_s_t         create_ts;
    unix_ts_s_t         update_ts;
    std::string         name;
};

}//namespace GPlatform
