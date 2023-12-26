#include "GpGeoFormatEsriShapeManager.hpp"

#include <GpCore2/GpUtils/Other/GpRAIIonDestruct.hpp>
#include <iostream>

namespace GPlatform {

GpGeoFormatEsriShapeManager::~GpGeoFormatEsriShapeManager (void) noexcept
{
}

GpGeoShape::C::Vec::Val GpGeoFormatEsriShapeManager::Read (std::u8string_view aFileName)
{
    const std::u8string fileName(aFileName);
    SHPHandle shpHandle = SHPOpen(GpUTF::S_As_STR(fileName.data()).data(), "rb");

    THROW_COND_GP
    (
        shpHandle != nullptr,
        [aFileName](){return u8"ESRI shape file '"_sv + aFileName + u8"' was not found"_sv;}
    );

    GpRAIIonDestruct onDesctruct
    (
        [shpHandle]()
        {
            SHPClose(shpHandle);
        }
    );

    std::array<double, 4>   adfMinBound;
    std::array<double, 4>   adfMaxBound;
    int                     nShapeType;
    int                     nEntities;

    SHPGetInfo(shpHandle, &nEntities, &nShapeType, adfMinBound.data(), adfMaxBound.data());

    GpGeoShape::C::Vec::Val geoShapes;
    geoShapes.reserve(NumOps::SConvert<size_t>(nEntities));

    for(int shapeId = 0; shapeId < nEntities; shapeId++)
    {
        SHPObject* shpObject = SHPReadObject(shpHandle, shapeId);

        GpRAIIonDestruct onDesctructObj
        (
            [shpObject]()
            {
                SHPDestroyObject(shpObject);
            }
        );

        geoShapes.emplace_back(ReadShape(shpObject));
    }

    return geoShapes;
}

void    GpGeoFormatEsriShapeManager::Write
(
    const GpGeoShape::C::Vec::Val&  aShapes,
    std::u8string_view              aFileName
)
{
    const std::u8string fileName(aFileName);
    SHPHandle shpHandle = SHPCreate(GpUTF::S_As_STR(fileName.data()).data(), SHPT_POLYGON);

    THROW_COND_GP
    (
        shpHandle != nullptr,
        [aFileName](){return u8"Can`t create ESRI shape file '"_sv + aFileName + u8"'"_sv;}
    );

    GpRAIIonDestruct onDesctruct
    (
        [shpHandle]()
        {
            SHPClose(shpHandle);
        }
    );

    size_t shapeId = 0;

    for (const GpGeoShape& shape: aShapes)
    {
        //Collect shape points to arrays
        const size_t            pointsCount     = shape.PointsCount();
        const size_t            contoursCount   = shape.Contours().size();
        GpGeoShape::PointsLatT  pointsLat;
        GpGeoShape::PointsLonT  pointsLon;
        std::vector<size_t>     contoursSize;

        std::tie(pointsLat, pointsLon, contoursSize) = shape.CollectPointsLatLon();

        std::vector<int> panPartStart;
        std::vector<int> panPartType;
        panPartStart.resize(contoursCount);
        panPartType.resize(contoursCount);

        for (size_t id = 0; id < contoursCount; id++)
        {
            panPartStart[id]= (id > 0) ? panPartStart[id-1] + int(contoursSize[id-1]) : 0;
            panPartType[id] = SHPT_POLYGON;
        }

        //Create an object
        SHPObject* shpObject = SHPCreateObject
        (
            SHPT_POLYGON,
            NumOps::SConvert<int>(shapeId++),
            NumOps::SConvert<int>(contoursCount),
            panPartStart.data(),
            panPartType.data(),
            NumOps::SConvert<int>(pointsCount),
            reinterpret_cast<const double*>(pointsLon.data()),
            reinterpret_cast<const double*>(pointsLat.data()),
            nullptr,
            nullptr
        );

        GpRAIIonDestruct onDesctructObj
        (
            [shpObject]()
            {
                if (shpObject)
                {
                    SHPDestroyObject(shpObject);
                }
            }
        );

        //Write the object to the shapefile
        THROW_COND_GP
        (
            SHPWriteObject(shpHandle, -1, shpObject) >= 0,
            u8"SHPWriteObject return -1"_sv
        );
    }
}

GpGeoShape  GpGeoFormatEsriShapeManager::ReadShape (SHPObject* aShapeObj) const
{
    GpGeoShape geoShape;

    //const int     defaultShapeObjType = aShapeObj->nSHPType;
    const size_t    partsCount          = NumOps::SConvert<size_t>(aShapeObj->nParts);
    const size_t    totalPointsCount    = NumOps::SConvert<size_t>(aShapeObj->nVertices);
    const int*      partType            = aShapeObj->panPartType;
    const int*      partStartPointId    = aShapeObj->panPartStart;
    const double*   pointsX             = aShapeObj->padfX;
    const double*   pointsY             = aShapeObj->padfY;

    THROW_COND_GP
    (
        partsCount >= 1,
        [partsCount](){return u8"Parts count "_sv + StrOps::SToString(partsCount);}
    );

    THROW_COND_GP
    (
        partType != nullptr,
        u8"partType is NULL"_sv
    );

    THROW_COND_GP
    (
        partStartPointId != nullptr,
        u8"partStartPointId is NULL"_sv
    );

    THROW_COND_GP
    (
        totalPointsCount > 0,
        u8"totalPointsCount == 0"_sv
    );

    THROW_COND_GP
    (
        pointsX != nullptr,
        u8"pointsX is NULL"_sv
    );

    THROW_COND_GP
    (
        pointsY != nullptr,
        u8"pointsY is NULL"_sv
    );

    for (size_t partId = 0; partId < partsCount; partId++)
    {
        THROW_COND_GP
        (
            partType[partId] == SHPT_POLYGON,
            u8"pointsY is NULL"_sv
        );

        const size_t startPointId   = NumOps::SConvert<size_t>(partStartPointId[partId]);
        const size_t endPointId     = (partId == (partsCount - 1))
                                      ? ((totalPointsCount - size_t(1)))
                                      : (size_t(partStartPointId[partId + 1]) - size_t(1));
        const size_t pointCount     = endPointId - startPointId + 1;

        GpGeoPolyline               contour;
        GpGeoPoint::C::Vec::Val&    points = contour.Points();

        points.resize(pointCount);

        for (size_t pointId = 0; pointId < pointCount; pointId++)
        {
            const double lat = pointsY[pointId + startPointId];
            const double lon = pointsX[pointId + startPointId];

            points[pointId].Set
            (
                geo_lat_t::SMake(lat),
                geo_lon_t::SMake(lon)
            );
        }

        geoShape.AddContour(std::move(contour));
    }

    //THROW_GP(u8"Unsupported shape type '"_sv + StrOps::SToString(shapeObjType) + u8"'"_sv);

    return geoShape;
}

}//namespace  GPlatform
