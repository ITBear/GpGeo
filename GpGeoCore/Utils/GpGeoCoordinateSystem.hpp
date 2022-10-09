#pragma once

#include "../GpGeoCore_global.hpp"

namespace GPlatform {

GP_ENUM(GP_GEO_CORE_API, GpGeoCoordinateSystem,
    WGS_84_4326,        //4326 (https://epsg.io/4326)
    WEB_MERCATOR_3857   //3857 (https://epsg.io/3857)
);

}//namespace GPlatform
