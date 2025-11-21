#include <GpGeo/GpGeoCore/GpGeoCoreLib.hpp>
#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>

GP_STATIC_INITIALIZER_IMPL(GpGeoCore)
GP_LIB_REGISTRATOR(GpGeoCoreLib)

void    GpGeoCore_StaticInitializer::OnInitialize (void)
{
    GpGeoCoreLib::SRegisterSelf();
}
