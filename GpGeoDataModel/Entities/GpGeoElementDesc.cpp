#include "GpGeoElementDesc.hpp"
#include "../../../GpCore2/GpReflection/GpReflectManager.hpp"

namespace GPlatform {

REFLECT_IMPLEMENT(GpGeoElementDesc, GP_MODULE_UUID)

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
