#pragma once

#include "../GpGeoDataModel_global.hpp"
#include "../../../GpCore2/GpUtils/Macro/GpMacroClass.hpp"
#include "../../../GpCore2/GpReflection/GpReflectObject.hpp"
#include "../../../GpCore2/GpReflection/GpReflectUtils.hpp"

namespace GPlatform {

class GP_GEO_DATA_MODEL_API GpGeoElementDesc final: public GpReflectObject
{
public:
    CLASS_DD(GpGeoElementDesc)
    REFLECT_DECLARE(u8"d767d127-5e8d-4359-593c-e177fc510fac"_uuid)

public:
                        GpGeoElementDesc        (void) noexcept = default;
    inline              GpGeoElementDesc        (const GpGeoElementDesc& aDesc);
    inline              GpGeoElementDesc        (GpGeoElementDesc&& aDesc) noexcept;
    virtual             ~GpGeoElementDesc       (void) noexcept override final;

public:
    GpUUID              id;
    GpUUID              type_id;
    unix_ts_s_t         create_ts;
    unix_ts_s_t         update_ts;
    GpUUID              parent_id;
    s_int_64            shape_id = 0;
};

GpGeoElementDesc::GpGeoElementDesc (const GpGeoElementDesc& aDesc):
GpReflectObject(aDesc),
id       (GpReflectUtils::SCopyValue(aDesc.id)),
type_id  (GpReflectUtils::SCopyValue(aDesc.type_id)),
create_ts(GpReflectUtils::SCopyValue(aDesc.create_ts)),
update_ts(GpReflectUtils::SCopyValue(aDesc.update_ts)),
parent_id(GpReflectUtils::SCopyValue(aDesc.parent_id)),
shape_id (GpReflectUtils::SCopyValue(aDesc.shape_id))
{
}

GpGeoElementDesc::GpGeoElementDesc (GpGeoElementDesc&& aDesc) noexcept:
GpReflectObject(std::move(aDesc)),
id       (std::move(aDesc.id)),
type_id  (std::move(aDesc.type_id)),
create_ts(std::move(aDesc.create_ts)),
update_ts(std::move(aDesc.update_ts)),
parent_id(std::move(aDesc.parent_id)),
shape_id (std::move(aDesc.shape_id))
{
}


}//namespace GPlatform
