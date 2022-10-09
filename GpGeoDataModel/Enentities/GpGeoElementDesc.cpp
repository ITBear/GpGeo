#include "GpGeoElementDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpGeoElementDesc, GP_MODULE_UUID)

GpGeoElementDesc::GpGeoElementDesc (void) noexcept
{
}

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

GpGeoElementDesc::~GpGeoElementDesc (void) noexcept
{
}

void    GpGeoElementDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& aPropsOut)
{
    {
        GpReflectPropFlags      f       = {GpReflectPropFlag::GENERATED_ONCE, GpReflectPropFlag::PRIMARY_KEY};
        GpReflectProp::GenFnT   genFn   = [](const auto& aProp, void* aDataPtr){aProp.Value_UUID(aDataPtr) = GpUUID::SGenRandomV7();};
        PROP_FG(id, f, genFn);
    }

    PROP(type_id);
    PROP_F(create_ts,   {GpReflectPropFlag::GENERATED_OUTSIDE});
    PROP_F(update_ts,   {GpReflectPropFlag::GENERATED_OUTSIDE});
    PROP(parent_id);
    PROP(shape_id);
}

}//namespace GPlatform
