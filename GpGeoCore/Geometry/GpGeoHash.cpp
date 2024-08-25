#include "GpGeoHash.hpp"

#include <GpCore2/GpUtils/Types/Strings/GpStringLiterals.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringOps.hpp>
#include <GpCore2/GpUtils/Types/Bits/GpBitOps.hpp>

namespace GPlatform {

constexpr const GpGeoHash::HashLen2Bits     GpGeoHash::sHashLen2Bits        = GpGeoHash::SHashLen2Bits();
constexpr const GpGeoHash::ZoneSizeWorldT   GpGeoHash::sSizeOfZonesWorld    = GpGeoHash::SSizeOfZonesWorld();

const GpGeoHash::AlphabetT      GpGeoHash::sAlphabet =
{
    '0','1','2','3','4','5','6','7','8','9','b','c','d','e','f','g','h','j','k','m','n','p','q','r','s','t','u','v','w','x','y','z'
};

std::string GpGeoHash::ToString (const size_t aHashLength) const
{
    THROW_COND_GP
    (
        (aHashLength >= 1) && (aHashLength <= 12),
        "aHashLength is out of range [1..12]"_sv
    );

    std::string hashStr;
    hashStr.resize(aHashLength);

    char* hashStrChar = std::data(hashStr);
    hashStrChar += (aHashLength - 1);

    u_int_64 hash = ValueAsUI64();

    for (size_t i = 0; i < aHashLength; i++)
    {
        const size_t id = size_t(hash) & size_t(0b11111);
        *hashStrChar-- = sAlphabet.at(id);

        hash >>= 5;
    }

    return hashStr;
}

void    GpGeoHash::FromString (std::string_view aHashStr)
{
    const size_t    hashStrLen  = std::size(aHashStr);
    const char*     hashStrChar = std::data(aHashStr);

    u_int_64 hash = 0;

    for (size_t i = 0; i < hashStrLen; i++)
    {
        const char      ch          = *hashStrChar++;
        const u_int_64  chInt       = u_int_64(ch);
        u_int_64        hashPart    = 0;

        if (NumOps::SIsBetween(ch, '0', '9'))
        {
            hashPart = u_int_64(0) + chInt - u_int_64('0');
        } else if (NumOps::SIsBetween(ch, 'b', 'h'))
        {
            hashPart = u_int_64(10) + chInt - u_int_64('b');
        } else if (NumOps::SIsBetween(ch, 'j', 'k'))
        {
            hashPart = u_int_64(17) + chInt - u_int_64('j');
        } else if (NumOps::SIsBetween(ch, 'm', 'n'))
        {
            hashPart = u_int_64(19) + chInt - u_int_64('m');
        } else if (NumOps::SIsBetween(ch, 'p', 'z'))
        {
            hashPart = u_int_64(21) + chInt - u_int_64('p');
        } else
        {
            THROW_GP("Wrong geohash value '"_sv + aHashStr + "', wrong character "_sv + std::string(&ch, 1));
        }

        hash <<= 5;
        hash |= hashPart;
    }

    iValue = std::bit_cast<value_type>(hash);
}

void    GpGeoHash::UpdateLength
(
    const size_t aOldLength,
    const size_t aNewLength
)
{
    THROW_COND_GP
    (
        (aOldLength >= 1) && (aOldLength <= 12),
        "aOldLength is out of range [1..12]"_sv
    );

    THROW_COND_GP
    (
        (aNewLength >= 1) && (aNewLength <= 12),
        "aNewLength is out of range [1..12]"_sv
    );

    if (aOldLength == aNewLength)
    {
        return;
    }

    const ssize_t delta = NumOps::SConvert<ssize_t>(aOldLength) - NumOps::SConvert<ssize_t>(aNewLength);

    if (delta > 0)//New length is shorter
    {
        SetValueUI64(ValueAsUI64() >> (5*delta));
    } else//New length is longer
    {
        SetValueUI64(ValueAsUI64() << (5*delta));
    }
}

std::array<GpGeoHash, 9>    GpGeoHash::Neighbours (const size_t aHashLength) const
{
    THROW_COND_GP
    (
        (aHashLength >= 1) && (aHashLength <= 12),
        "aHashLength is out of range [1..12]"_sv
    );

    const GpGeoAABB     thisAabb    = ToAABB(aHashLength);
    const GpGeoPoint&   aabbCentral = thisAabb.Center();
    const geo_lat_t     deltaLat    = thisAabb.HalfSizeLat() * 2.0_geo_lat;
    const geo_lon_t     deltaLon    = thisAabb.HalfSizeLon() * 2.0_geo_lon;

    const geo_lat_t     bottomLat   = aabbCentral.Lat() - deltaLat;
    const geo_lat_t     centerLat   = aabbCentral.Lat();
    const geo_lat_t     upLat       = aabbCentral.Lat() + deltaLat;

    const geo_lon_t     leftLon     = aabbCentral.Lon() - deltaLon;
    const geo_lon_t     centerLon   = aabbCentral.Lon();
    const geo_lon_t     rightLon    = aabbCentral.Lon() + deltaLon;


    const GpGeoHash upLeft      (GpGeoPoint(upLat,     leftLon),   aHashLength);
    const GpGeoHash upCenter    (GpGeoPoint(upLat,     centerLon), aHashLength);
    const GpGeoHash upRight     (GpGeoPoint(upLat,     rightLon),  aHashLength);

    const GpGeoHash centerLeft  (GpGeoPoint(centerLat, leftLon),   aHashLength);
    const GpGeoHash centerCenter(GpGeoPoint(centerLat, centerLon), aHashLength);
    const GpGeoHash centerRight (GpGeoPoint(centerLat, rightLon),  aHashLength);

    const GpGeoHash bottomLeft  (GpGeoPoint(bottomLat, leftLon),   aHashLength);
    const GpGeoHash bottomCenter(GpGeoPoint(bottomLat, centerLon), aHashLength);
    const GpGeoHash bottomRight (GpGeoPoint(bottomLat, rightLon),  aHashLength);

    return
    {
        upLeft,     upCenter,     upRight,
        centerLeft, centerCenter, centerRight,
        bottomLeft, bottomCenter, bottomRight
    };
}

GpGeoHash::OneOrVectorValT  GpGeoHash::Neighbours
(
    const size_t aHashLength,
    const size_t aHashOffsetCount
) const
{
    THROW_COND_GP
    (
        (aHashLength >= 1) && (aHashLength <= 12),
        "aHashLength is out of range [1..12]"_sv
    );

    const GpGeoAABB     thisAabb    = ToAABB(aHashLength);
    const geo_lat_t     deltaLat    = thisAabb.HalfSizeLat() * 2.0_geo_lat * geo_lat_t::SMake(aHashOffsetCount);
    const geo_lon_t     deltaLon    = thisAabb.HalfSizeLon() * 2.0_geo_lon * geo_lon_t::SMake(aHashOffsetCount);

    return SFromAABB
    (
        GpGeoAABB::SFromCentralPoint
        (
            thisAabb.Center(),
            deltaLat,
            deltaLon
        ),
        aHashLength
    );
}

/*GpGeoHash GpGeoHash::CropToLength (const size_t aHashLength) const
{
    THROW_COND_GP
    (
        (aHashLength >= 1) && (aHashLength <= 12),
        "aHashLength is out of range [1..12]"_sv
    );

    GpGeoHash newHash;

    newHash.FromPoint
    (
        ToPoint(aHashLength),
        aHashLength
    );

    return newHash;
}*/

GpGeoPoint  GpGeoHash::ToPoint
(
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB
) const
{
    const auto[latBitsCount, lonBitsCount] = GpGeoHash::sHashLen2Bits.at(aHashLength);

    const GpGeoPoint aabbMin = aWorldAABB.Min();
    const GpGeoPoint aabbMax = aWorldAABB.Max();

    auto[latBits, lonBits] = BitOps::Deinterleave32_32(ValueAsUI64());

    if (latBitsCount == lonBitsCount)
    {
        std::swap(latBits, lonBits);
    }

    const geo_lat_t lat = geo_lat_t::SMake
    (
        SDecode
        (
            u_int_64(latBits),
            aabbMin.Lat().Value(),
            aabbMax.Lat().Value(),
            latBitsCount
        )
    );

    const geo_lon_t lon = geo_lon_t::SMake
    (
        SDecode
        (
            u_int_64(lonBits),
            aabbMin.Lon().Value(),
            aabbMax.Lon().Value(),
            lonBitsCount
        )
    );

    return GpGeoPoint(lat, lon);
}

void    GpGeoHash::FromPoint
(
    const geo_lat_t     aLat,
    const geo_lon_t     aLon,
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB
)
{
    const auto[latBitsCount, lonBitsCount] = GpGeoHash::sHashLen2Bits.at(aHashLength);

    const GpGeoPoint aabbMin = aWorldAABB.Min();
    const GpGeoPoint aabbMax = aWorldAABB.Max();

    const u_int_64 latBits = SEncode
    (
        aLat.Value(),
        aabbMin.Lat().Value(),
        aabbMax.Lat().Value(),
        latBitsCount
    );

    const u_int_64 lonBits = SEncode
    (
        aLon.Value(),
        aabbMin.Lon().Value(),
        aabbMax.Lon().Value(),
        lonBitsCount
    );

    u_int_64 hash = 0;

    if (latBitsCount == lonBitsCount)
    {
        hash = BitOps::Interleave32_32(u_int_32(lonBits), u_int_32(latBits));
    } else
    {
        hash = BitOps::Interleave32_32(u_int_32(latBits), u_int_32(lonBits));
    }

    iValue = std::bit_cast<value_type>(hash);
}

GpGeoHash::OneOrVectorValT  GpGeoHash::SFromAABB
(
    const GpGeoAABB&    aAABB,
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB
)
{
    GpGeoHash minPointGeoHash;
    GpGeoHash maxPointGeoHash;

    minPointGeoHash.FromPoint(aAABB.Min(), aHashLength, aWorldAABB);
    maxPointGeoHash.FromPoint(aAABB.Max(), aHashLength, aWorldAABB);

    if (minPointGeoHash == maxPointGeoHash)
    {
        return minPointGeoHash;
    }

    return SMakeZones(minPointGeoHash, maxPointGeoHash, aHashLength);
}

GpGeoHash::OneOrVectorValT  GpGeoHash::SMakeZones
(
    const GpGeoHash&    aMinPointGeoHash,
    const GpGeoHash&    aMaxPointGeoHash,
    const size_t        aHashLength
)
{
    if (aMinPointGeoHash == aMaxPointGeoHash)
    {
        return aMinPointGeoHash;
    }

    const auto[latBitsCount, lonBitsCount] = GpGeoHash::sHashLen2Bits.at(aHashLength);

    const auto bitsMinVal = BitOps::Deinterleave32_32(aMinPointGeoHash.ValueAsUI64());
    const auto bitsMaxMax = BitOps::Deinterleave32_32(aMaxPointGeoHash.ValueAsUI64());

    u_int_32 latBitsMin;
    u_int_32 lonBitsMin;
    u_int_32 latBitsMax;
    u_int_32 lonBitsMax;

    const bool isLatLonBitsCountEqual = (latBitsCount == lonBitsCount);

    if (isLatLonBitsCountEqual)
    {
        latBitsMin = std::get<1>(bitsMinVal);
        lonBitsMin = std::get<0>(bitsMinVal);
        latBitsMax = std::get<1>(bitsMaxMax);
        lonBitsMax = std::get<0>(bitsMaxMax);
    } else
    {
        latBitsMin = std::get<0>(bitsMinVal);
        lonBitsMin = std::get<1>(bitsMinVal);
        latBitsMax = std::get<0>(bitsMaxMax);
        lonBitsMax = std::get<1>(bitsMaxMax);
    }

    const size_t latZonesCount  = size_t(latBitsMax - latBitsMin) + 1;
    const size_t lonZonesCount  = size_t(lonBitsMax - lonBitsMin) + 1;
    const size_t zonesCount     = latZonesCount * lonZonesCount;

    GpGeoHash::C::Vec::Val res;
    res.reserve(zonesCount);

    u_int_32 latBits = latBitsMin;
    u_int_32 lonBits = lonBitsMin;

    for (size_t latId = 0; latId < latZonesCount; ++latId)
    {
        for (size_t lonId = 0; lonId < lonZonesCount; ++lonId)
        {
            const u_int_64 geohash =
                  (BitOps::Interleave32_32(u_int_32(lonBits), u_int_32(latBits)) * u_int_64(isLatLonBitsCountEqual))
                | (BitOps::Interleave32_32(u_int_32(latBits), u_int_32(lonBits)) * (u_int_64(1) - u_int_64(isLatLonBitsCountEqual)));

            res.emplace_back(geohash);

            lonBits++;
        }

        latBits++;
        lonBits = lonBitsMin;
    }

    return res;
}

u_int_64    GpGeoHash::SEncode
(
    const double     aSrcValue,
    const double     aMin,
    const double     aMax,
    const size_bit_t aBitsCount
) noexcept
{
    u_int_64    encodedValue    = 0;
    double      min             = aMin;
    double      max             = aMax;

    const size_t bitsCount = aBitsCount.Value();

    for (size_t i = 0; i < bitsCount; i++)
    {
        encodedValue <<= 1;

        const double mid = (min + max)*0.5;

        if (aSrcValue >= mid)
        {
            min             = mid;
            encodedValue    |= 1;
        } else
        {
            max             = mid;
            encodedValue    |= 0;
        }
    }

    return encodedValue;
}

double  GpGeoHash::SDecode
(
    const u_int_64      aEncodedValue,
    const double        aMin,
    const double        aMax,
    const size_bit_t    aBitsCount
) noexcept
{
    double min      = aMin;
    double max      = aMax;
    double mid      = (min + max)*0.5;

    const size_t bitsCount = aBitsCount.Value();

    size_t bitsMask = size_t(1) << size_t(bitsCount - 1);

    for (size_t i = 0; i < bitsCount; i++)
    {
        if (aEncodedValue & bitsMask)
        {
            min = mid;
        } else
        {
            max = mid;
        }

        bitsMask >>= 1;

        mid = (min + max)*0.5;
    }

    return mid;
}

}// namespace GPlatform
