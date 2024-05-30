#include "GpGeoElementNameDesc.hpp"

#include <GpCore2/GpReflection/GpReflectManager.hpp>
#include <GpCore2/GpReflection/GpReflectPropUtils.hpp>

namespace GPlatform {

REFLECT_IMPLEMENT(GpGeoElementNameDesc, GP_MODULE_UUID)

GpGeoElementNameDesc::~GpGeoElementNameDesc (void) noexcept
{
}

void    GpGeoElementNameDesc::_SReflectCollectProps (GpReflectProp::SmallVecVal& aPropsOut)
{
    PROP_F(id,          {GpReflectPropFlag::PRIMARY_KEY});
    PROP_F(language_id, {GpReflectPropFlag::PRIMARY_KEY});
    PROP_F(create_ts,   {GpReflectPropFlag::GENERATED_OUTSIDE});
    PROP_F(update_ts,   {GpReflectPropFlag::GENERATED_OUTSIDE});
    PROP  (name);
}

}// namespace GPlatform
