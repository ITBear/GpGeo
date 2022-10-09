#include "GpGeoElementNameDesc.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpGeoElementNameDesc, GP_MODULE_UUID)

GpGeoElementNameDesc::GpGeoElementNameDesc (void) noexcept
{
}

GpGeoElementNameDesc::GpGeoElementNameDesc (const GpGeoElementNameDesc& aDesc):
GpReflectObject(aDesc),
id(aDesc.id),
language_id(aDesc.language_id),
create_ts(aDesc.create_ts),
update_ts(aDesc.update_ts),
name(aDesc.name)
{
}

GpGeoElementNameDesc::GpGeoElementNameDesc (GpGeoElementNameDesc&& aDesc) noexcept:
GpReflectObject(std::move(aDesc)),
id(std::move(aDesc.id)),
language_id(std::move(aDesc.language_id)),
create_ts(std::move(aDesc.create_ts)),
update_ts(std::move(aDesc.update_ts)),
name(std::move(aDesc.name))
{
}

GpGeoElementNameDesc::~GpGeoElementNameDesc (void) noexcept
{
}

void    GpGeoElementNameDesc::_SReflectCollectProps (GpReflectProp::C::Vec::Val& aPropsOut)
{
    PROP_F(id,          {GpReflectPropFlag::PRIMARY_KEY});
    PROP_F(language_id, {GpReflectPropFlag::PRIMARY_KEY});
    PROP_F(create_ts,   {GpReflectPropFlag::GENERATED_OUTSIDE});
    PROP_F(update_ts,   {GpReflectPropFlag::GENERATED_OUTSIDE});
    PROP(name);
}

}//namespace GPlatform
