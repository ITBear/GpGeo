#include "GpGeoToString.hpp"

namespace GPlatform {

std::string GpGeoToString::SToString (const GpGeoShape& aShape)
{
    std::string resStr;
    resStr.reserve(512);

    size_t contourId = 0;

    for (const GpGeoPolyline& contour: aShape.Contours())
    {
        if (contourId > 0)
        {
            resStr.append("\n"_sv);
        }

        resStr.append("contour_"_sv + contourId + ": ["_sv);

        for (const GpGeoPoint& point: contour.Points())
        {
            resStr.append("("_sv + point.Lat().Value() + ", "_sv + point.Lon().Value() + ")");
        }

        resStr.append("]"_sv);

        contourId++;
    }

    return resStr;
}

}//namespace GPlatform
