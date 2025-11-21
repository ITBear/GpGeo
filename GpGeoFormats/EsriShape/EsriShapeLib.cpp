#include <GpGeo/GpGeoFormats/EsriShape/EsriShapeLib.hpp>
#include <GpCore2/GpUtils/Other/GpLinkedLibsInfo.hpp>

GP_STATIC_INITIALIZER_IMPL(EsriShape)
GP_LIB_REGISTRATOR(EsriShapeLib)

void    EsriShape_StaticInitializer::OnInitialize (void)
{
    EsriShapeLib::SRegisterSelf();
}
