#pragma once

#include <GpCore2/GpUtils/Macro/GpMacroWarnings.hpp>

GP_WARNING_PUSH()
GP_WARNING_DISABLE(sign-conversion)
GP_WARNING_DISABLE(unused-parameter)
GP_WARNING_DISABLE(float-equal)
GP_WARNING_DISABLE(shadow)
GP_WARNING_DISABLE(double-promotion)

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_point.hpp>
#include <boost/geometry/geometries/box.hpp>

GP_WARNING_POP()

using Boost_PointT      = boost::geometry::model::d2::point_xy<double>;
using Boost_PolygonT    = boost::geometry::model::polygon<Boost_PointT>;
using Boost_BoxT        = boost::geometry::model::box<Boost_PointT>;
using Boost_LinestringT = boost::geometry::model::linestring<Boost_PointT>;

namespace GPlatform {

class GpGeoShapeCacheImpl
{
public:
    Boost_LinestringT       iLinestring;
    Boost_PolygonT          iPolygon;
    bool                    iIsFill = false;
};

}//namespace GPlatform
