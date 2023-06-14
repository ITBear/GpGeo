#pragma once

#include "../../Geometry/GpGeoPoint.hpp"
#include "../GpGeoCoordinateSystem.hpp"
#include "GpGeoCC_Wgs84_WebMercator.hpp"

namespace GPlatform {

class GpGeoCoordinateConverter;

using GeoCC = GpGeoCoordinateConverter;

class GpGeoCoordinateConverter
{
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(GpGeoCoordinateConverter)

public:
    template<GpGeoCoordinateSystem::EnumT FROM,
             GpGeoCoordinateSystem::EnumT TO>
    static          GpGeoPoint  SConvert                (const GpGeoPoint& aPoint) noexcept;

    inline static   GpGeoPoint  SWgs84_To_WebMercator   (const GpGeoPoint& aPoint) noexcept;
    inline static   GpGeoPoint  SWebMercator_To_Wgs84   (const GpGeoPoint& aPoint) noexcept;
};

template<GpGeoCoordinateSystem::EnumT FROM,
         GpGeoCoordinateSystem::EnumT TO>
GpGeoPoint  GpGeoCoordinateConverter::SConvert (const GpGeoPoint& aPoint) noexcept
{
    if constexpr (FROM == GpGeoCoordinateSystem::WGS_84_4326)
    {
        if constexpr (TO == GpGeoCoordinateSystem::WGS_84_4326)
        {
            return aPoint;
        } else if constexpr (TO == GpGeoCoordinateSystem::WEB_MERCATOR_3857)
        {
            return SWgs84_To_WebMercator(aPoint);
        } else
        {
            GpThrowCe<GpException>(u8"Unsupported TO GeoCoordinateSystem FROM WGS_84_EPSG_4326");
        }
    } else if constexpr (FROM == GpGeoCoordinateSystem::WEB_MERCATOR_3857)
    {
        if constexpr (TO == GpGeoCoordinateSystem::WEB_MERCATOR_3857)
        {
            return aPoint;
        } else if constexpr (TO == GpGeoCoordinateSystem::WGS_84_4326)
        {
            return SWebMercator_To_Wgs84(aPoint);
        } else
        {
            GpThrowCe<GpException>(u8"Unsupported TO GeoCoordinateSystem FROM WEB_MERCATOR_3857");
        }
    } else
    {
        GpThrowCe<GpException>(u8"Unsupported FROM GeoCoordinateSystem");
    }
}

GpGeoPoint  GpGeoCoordinateConverter::SWgs84_To_WebMercator (const GpGeoPoint& aPoint) noexcept
{
    return GpGeoCC_Wgs84_WebMercator::CCForward(aPoint);
}

GpGeoPoint  GpGeoCoordinateConverter::SWebMercator_To_Wgs84 (const GpGeoPoint& aPoint) noexcept
{
    return GpGeoCC_Wgs84_WebMercator::CCBackward(aPoint);
}

}//namespace GPlatform
