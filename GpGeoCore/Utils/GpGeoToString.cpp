#include "GpGeoToString.hpp"

#include <sstream>

namespace GPlatform {

template <typename T>
std::string __SToString
(
    const T         aValue,
    const size_t    aPrecision
)
{
    std::ostringstream out;
    out.precision(int(aPrecision));
    out << std::fixed << aValue;
    return std::string(out.str());
}

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
            resStr.append("("_sv + __SToString(point.Lat().Value(), 14) + ", "_sv + __SToString(point.Lon().Value(), 14) + ")");
        }

        resStr.append("]"_sv);

        contourId++;
    }

    return resStr;
}

}// namespace GPlatform
