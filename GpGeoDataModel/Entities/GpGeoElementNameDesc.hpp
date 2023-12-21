#pragma once

#include "../GpGeoDataModel_global.hpp"

#include <GpCore2/GpUtils/Macro/GpMacroClass.hpp>
#include <GpCore2/GpReflection/GpReflectObject.hpp>
#include <GpCore2/GpReflection/GpReflectUtils.hpp>

namespace GPlatform {

class GP_GEO_DATA_MODEL_API GpGeoElementNameDesc final: public GpReflectObject
{
public:
    CLASS_DD(GpGeoElementNameDesc)
    REFLECT_DECLARE(u8"aa18b505-27d2-450d-cb44-9021becc25ae"_uuid)

public:
                        GpGeoElementNameDesc        (void) noexcept = default;
    inline              GpGeoElementNameDesc        (const GpGeoElementNameDesc& aDesc);
    inline              GpGeoElementNameDesc        (GpGeoElementNameDesc&& aDesc) noexcept;
    virtual             ~GpGeoElementNameDesc       (void) noexcept override final;

public:
    GpUUID              id;
    s_int_32            language_id;
    unix_ts_s_t         create_ts;
    unix_ts_s_t         update_ts;
    std::u8string       name;
};

GpGeoElementNameDesc::GpGeoElementNameDesc (const GpGeoElementNameDesc& aDesc):
GpReflectObject(aDesc),
id         (GpReflectUtils::SCopyValue(aDesc.id)),
language_id(GpReflectUtils::SCopyValue(aDesc.language_id)),
create_ts  (GpReflectUtils::SCopyValue(aDesc.create_ts)),
update_ts  (GpReflectUtils::SCopyValue(aDesc.update_ts)),
name       (GpReflectUtils::SCopyValue(aDesc.name))
{
}

GpGeoElementNameDesc::GpGeoElementNameDesc (GpGeoElementNameDesc&& aDesc) noexcept:
GpReflectObject(std::move(aDesc)),
id         (std::move(aDesc.id)),
language_id(std::move(aDesc.language_id)),
create_ts  (std::move(aDesc.create_ts)),
update_ts  (std::move(aDesc.update_ts)),
name       (std::move(aDesc.name))
{
}

}//namespace GPlatform
