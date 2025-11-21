#include <GpGeo/GpGeoDataModel/GpGeoDataModelLib.hpp>
#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>

GP_STATIC_INITIALIZER_IMPL(GpGeoDataModel)
GP_LIB_REGISTRATOR(GpGeoDataModelLib)

void    GpGeoDataModel_StaticInitializer::OnInitialize (void)
{
    GpGeoDataModelLib::SRegisterSelf();
}
