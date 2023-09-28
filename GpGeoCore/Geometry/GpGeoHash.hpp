#pragma once

#include "GpGeoAABB.hpp"
#include "../../../GpCore2/GpUtils/Types/Units/Other/size_byte_t.hpp"

#include <variant>
#include <bit>

namespace GPlatform {

class GP_GEO_CORE_API GpGeoHash
{
public:
    CLASS_DD(GpGeoHash)

public:
    using value_type        = std::array<std::byte, 8>;
    using BitsCount         = std::tuple<size_bit_t/*lat*/, size_bit_t/*lon*/>;
    using HashLen2Bits      = std::array<BitsCount, 1 + 12>;
    using AlphabetT         = std::array<char8_t, 32>;
    using OneOrVectorValT   = std::variant<GpGeoHash, GpGeoHash::C::Vec::Val>;
    using ZoneSizeT         = std::tuple<geo_lat_t, geo_lon_t>;
    using ZoneSizeWorldT    = std::array<ZoneSizeT, 1 + 12>;

public:
    constexpr inline            GpGeoHash           (void) noexcept;
    constexpr inline            GpGeoHash           (const GpGeoHash& aGeohash) noexcept;
    constexpr inline            GpGeoHash           (GpGeoHash&& aGeohash) noexcept;
    constexpr inline            GpGeoHash           (const GpGeoPoint&  aPoint,
                                                     const size_t       aHashLength);
    constexpr inline            GpGeoHash           (const GpGeoPoint&  aPoint,
                                                     const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB);
    constexpr inline            GpGeoHash           (const geo_lat_t    aLat,
                                                     const geo_lon_t    aLon,
                                                     const size_t       aHashLength);
    constexpr inline            GpGeoHash           (const geo_lat_t    aLat,
                                                     const geo_lon_t    aLon,
                                                     const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB);
    constexpr inline            GpGeoHash           (const value_type   aRawValue) noexcept;
    constexpr inline            GpGeoHash           (const u_int_64     aRawValue) noexcept;

#if  (__cplusplus >= CPP_VERSION_20)
    constexpr inline            ~GpGeoHash          (void) noexcept;
#else
    inline                      ~GpGeoHash          (void) noexcept;
#endif//#if  (__cplusplus >= CPP_VERSION_20)

    constexpr inline GpGeoHash& operator=           (const GpGeoHash& aGeohash) noexcept;
    constexpr inline GpGeoHash& operator=           (GpGeoHash&& aGeohash) noexcept;
    constexpr inline bool       operator==          (const GpGeoHash& aGeohash) const noexcept;
    constexpr inline bool       operator>           (const GpGeoHash& aGeohash) const noexcept;
    constexpr inline bool       operator<           (const GpGeoHash& aGeohash) const noexcept;

    constexpr const value_type& Value               (void) const noexcept {return iValue;}
    constexpr u_int_64          ValueAsUI64         (void) const noexcept {return std::bit_cast<u_int_64>(iValue);}
    constexpr void              SetValueUI64        (const u_int_64 aValue) noexcept {iValue = std::bit_cast<value_type>(aValue);}

    std::u8string               ToString            (const size_t aHashLength) const;
    void                        FromString          (std::u8string_view aHashStr);

    void                        UpdateLength        (const size_t aOldLength,
                                                     const size_t aNewLength);
    std::array<GpGeoHash, 9>    Neighbours          (const size_t aHashLength) const;
    OneOrVectorValT             Neighbours          (const size_t aHashLength,
                                                     const size_t aHashOffsetCount) const;


    GpGeoPoint                  ToPoint             (const size_t       aHashLength) const {return ToPoint(aHashLength, GpGeoAABB(GpGeoAABB::ALL_SPHERE_WGS84));}
    GpGeoPoint                  ToPoint             (const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB) const;
    void                        FromPoint           (const GpGeoPoint&  aPoint,
                                                     const size_t       aHashLength) {FromPoint(aPoint.Lat(), aPoint.Lon(), aHashLength);}
    void                        FromPoint           (const GpGeoPoint&  aPoint,
                                                     const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB) {FromPoint(aPoint.Lat(), aPoint.Lon(), aHashLength, aWorldAABB);}
    void                        FromPoint           (const geo_lat_t    aLat,
                                                     const geo_lon_t    aLon,
                                                     const size_t       aHashLength) {FromPoint(aLat, aLon, aHashLength, GpGeoAABB(GpGeoAABB::ALL_SPHERE_WGS84));}
    void                        FromPoint           (const geo_lat_t    aLat,
                                                     const geo_lon_t    aLon,
                                                     const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB);
    inline GpGeoAABB            ToAABB              (const size_t       aHashLength) const;
    inline GpGeoAABB            ToAABB              (const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB,
                                                     const ZoneSizeT&   aPrecomputeSizeOfZone) const;

    static OneOrVectorValT      SFromAABB           (const GpGeoAABB&   aAABB,
                                                     const size_t       aHashLength) {return SFromAABB(aAABB, aHashLength, GpGeoAABB(GpGeoAABB::ALL_SPHERE_WGS84));}
    static OneOrVectorValT      SFromAABB           (const GpGeoAABB&   aAABB,
                                                     const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB);
    inline static GpGeoHash     SFromString         (std::u8string_view aHashStr);
    static OneOrVectorValT      SMakeZones          (const GpGeoHash&   aMinPointGeoHash,
                                                     const GpGeoHash&   aMaxPointGeoHash,
                                                     const size_t       aHashLength);
    inline static constexpr ZoneSizeT
                                SCalcSizeOfZone     (const size_t       aHashLength,
                                                     const GpGeoAABB&   aWorldAABB);

    inline static constexpr     HashLen2Bits
                                SHashLen2Bits       (void) noexcept;

    inline static constexpr     ZoneSizeWorldT
                                SSizeOfZonesWorld   (void);

    inline static constexpr     ZoneSizeT
                                SSizeOfZoneWorld    (const size_t aHashLength);

    static u_int_64             SEncode             (const double       aSrcValue,
                                                     const double       aMin,
                                                     const double       aMax,
                                                     const size_bit_t   aBitsCount) noexcept;
    static double               SDecode             (const u_int_64     aEncodedValue,
                                                     const double       aMin,
                                                     const double       aMax,
                                                     const size_bit_t   aBitsCount) noexcept;

private:
    value_type                  iValue;
    static const HashLen2Bits   sHashLen2Bits;
    static const ZoneSizeWorldT sSizeOfZonesWorld;

public:
    static const AlphabetT      sAlphabet;
};

constexpr GpGeoHash::GpGeoHash (void) noexcept
{
    iValue.fill(std::byte(0));
}

constexpr GpGeoHash::GpGeoHash (const GpGeoHash& aGeohash) noexcept:
iValue(aGeohash.iValue)
{
}

constexpr GpGeoHash::GpGeoHash (GpGeoHash&& aGeohash) noexcept:
iValue(aGeohash.iValue)
{
}

constexpr GpGeoHash::GpGeoHash
(
    const GpGeoPoint&   aPoint,
    const size_t        aHashLength
)
{
    FromPoint(aPoint, aHashLength);
}

constexpr GpGeoHash::GpGeoHash
(
    const GpGeoPoint&   aPoint,
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB
)
{
    FromPoint(aPoint, aHashLength, aWorldAABB);
}

constexpr GpGeoHash::GpGeoHash
(
    const geo_lat_t aLat,
    const geo_lon_t aLon,
    const size_t    aHashLength
)
{
    FromPoint(aLat, aLon, aHashLength);
}

constexpr GpGeoHash::GpGeoHash
(
    const geo_lat_t     aLat,
    const geo_lon_t     aLon,
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB
)
{
    FromPoint(aLat, aLon, aHashLength, aWorldAABB);
}

constexpr GpGeoHash::GpGeoHash (const value_type aRawValue) noexcept:
iValue(aRawValue)
{
}

constexpr GpGeoHash::GpGeoHash (const u_int_64 aRawValue) noexcept:
iValue(std::bit_cast<value_type>(aRawValue))
{
}

#if  (__cplusplus >= CPP_VERSION_20)
constexpr GpGeoHash::~GpGeoHash (void) noexcept
{
}
#else
GpGeoHash::~GpGeoHash (void) noexcept
{
}
#endif//#if  (__cplusplus >= CPP_VERSION_20)

constexpr GpGeoHash&    GpGeoHash::operator= (const GpGeoHash& aGeohash) noexcept
{
    iValue = aGeohash.iValue;

    return *this;
}

constexpr GpGeoHash&    GpGeoHash::operator= (GpGeoHash&& aGeohash) noexcept
{
    iValue = std::move(aGeohash.iValue);

    return *this;
}

constexpr bool  GpGeoHash::operator== (const GpGeoHash& aGeohash) const noexcept
{
    return iValue == aGeohash.iValue;
}

constexpr bool  GpGeoHash::operator> (const GpGeoHash& aGeohash) const noexcept
{
    return ValueAsUI64() > aGeohash.ValueAsUI64();
}

constexpr bool  GpGeoHash::operator< (const GpGeoHash& aGeohash) const noexcept
{
    return ValueAsUI64() < aGeohash.ValueAsUI64();
}

GpGeoAABB   GpGeoHash::ToAABB (const size_t aHashLength) const
{
    const ZoneSizeT size = sSizeOfZonesWorld.at(aHashLength);

    return ToAABB
    (
        aHashLength,
        GpGeoAABB(GpGeoAABB::ALL_SPHERE_WGS84),
        size
    );
}

GpGeoAABB   GpGeoHash::ToAABB
(
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB,
    const ZoneSizeT&    aPrecomputeSizeOfZone
) const
{
    const GpGeoPoint centralPoint = ToPoint(aHashLength, aWorldAABB);
    return GpGeoAABB::SFromCentralPoint
    (
        centralPoint,
        std::get<0>(aPrecomputeSizeOfZone),
        std::get<1>(aPrecomputeSizeOfZone)
    );
}

GpGeoHash   GpGeoHash::SFromString (std::u8string_view aHashStr)
{
    GpGeoHash h;
    h.FromString(aHashStr);
    return h;
}

constexpr GpGeoHash::ZoneSizeT  GpGeoHash::SCalcSizeOfZone
(
    const size_t        aHashLength,
    const GpGeoAABB&    aWorldAABB
)
{
    BitsCount bitsCount;

    if (std::is_constant_evaluated())
    {
        bitsCount = GpGeoHash::SHashLen2Bits().at(aHashLength);
    } else
    {
        bitsCount = GpGeoHash::sHashLen2Bits.at(aHashLength);
    }

    const GpAabb2d& worldAABB = aWorldAABB._InnerAABB();

    const double latSize = (worldAABB.Max().X() - worldAABB.Min().X())
                            / double(u_int_64(1) << u_int_64(std::get<0>(bitsCount).Value()));
    const double lonSize = (worldAABB.Max().Y() - worldAABB.Min().Y())
                            / double(u_int_64(1) << u_int_64(std::get<1>(bitsCount).Value()));

    return {geo_lat_t::SMake(latSize), geo_lon_t::SMake(lonSize)};
}

constexpr   GpGeoHash::HashLen2Bits GpGeoHash::SHashLen2Bits (void) noexcept
{
    constexpr const HashLen2Bits bl
    {
        BitsCount{ 0_bit,  0_bit}, // 0 - fill gap
        BitsCount{ 2_bit,  3_bit}, // 1
        BitsCount{ 5_bit,  5_bit}, // 2
        BitsCount{ 7_bit,  8_bit}, // 3
        BitsCount{10_bit, 10_bit}, // 4
        BitsCount{12_bit, 13_bit}, // 5
        BitsCount{15_bit, 15_bit}, // 6
        BitsCount{17_bit, 18_bit}, // 7
        BitsCount{20_bit, 20_bit}, // 8
        BitsCount{22_bit, 23_bit}, // 9
        BitsCount{25_bit, 25_bit}, //10
        BitsCount{27_bit, 28_bit}, //11
        BitsCount{30_bit, 30_bit}  //12
    };

    return bl;
}

constexpr GpGeoHash::ZoneSizeWorldT GpGeoHash::SSizeOfZonesWorld (void)
{   
    constexpr const GpGeoAABB aabb = GpGeoAABB(GpGeoAABB::ALL_SPHERE_WGS84);

    constexpr const ZoneSizeWorldT sizes
    {
        ZoneSizeT{0.0_geo_lat, 0.0_geo_lon}, // 0 - fill gap
        SCalcSizeOfZone( 1, aabb),
        SCalcSizeOfZone( 2, aabb),
        SCalcSizeOfZone( 3, aabb),
        SCalcSizeOfZone( 4, aabb),
        SCalcSizeOfZone( 5, aabb),
        SCalcSizeOfZone( 6, aabb),
        SCalcSizeOfZone( 7, aabb),
        SCalcSizeOfZone( 8, aabb),
        SCalcSizeOfZone( 9, aabb),
        SCalcSizeOfZone(10, aabb),
        SCalcSizeOfZone(11, aabb),
        SCalcSizeOfZone(12, aabb)
    };

    return sizes;
}

constexpr   GpGeoHash::ZoneSizeT    GpGeoHash::SSizeOfZoneWorld (size_t aHashLength)
{
    return SSizeOfZonesWorld().at(aHashLength);
}

}//namespace GPlatform

//*******************************************
namespace std {

template<>
struct hash<GPlatform::GpGeoHash>
{
    constexpr std::size_t operator()(const GPlatform::GpGeoHash& aGeoHash) const noexcept
    {
        static_assert(sizeof(std::size_t) == sizeof(u_int_64));
        return aGeoHash.ValueAsUI64();
    }
};

}//std

