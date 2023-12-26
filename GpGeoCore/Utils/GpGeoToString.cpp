#include "GpGeoToString.hpp"

#include <sstream>

namespace GPlatform {

template <typename T>
std::u8string __SToString
(
    const T         aValue,
    const size_t    aPrecision
)
{
    std::ostringstream out;
    out.precision(int(aPrecision));
    out << std::fixed << aValue;
    return std::u8string(GpUTF::S_As_UTF8(out.str()));
}

std::u8string   GpGeoToString::SToString (const GpGeoShape& aShape)
{
    std::u8string resStr;
    resStr.reserve(512);

    size_t contourId = 0;

    for (const GpGeoPolyline& contour: aShape.Contours())
    {
        if (contourId > 0)
        {
            resStr.append(u8"\n"_sv);
        }

        resStr.append(u8"contour_"_sv + contourId + u8": ["_sv);

        for (const GpGeoPoint& point: contour.Points())
        {
            resStr.append(u8"("_sv + __SToString(point.Lat().Value(), 14) + u8", "_sv + __SToString(point.Lon().Value(), 14) + u8")");
        }

        resStr.append(u8"]"_sv);

        contourId++;
    }

    return resStr;
}

}//namespace GPlatform
