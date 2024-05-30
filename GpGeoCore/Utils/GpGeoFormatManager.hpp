#pragma once

#include "../GpGeoCore_global.hpp"
#include "../Geometry/GpGeoShape.hpp"

#include <GpCore2/GpUtils/Macro/GpMacroClass.hpp>
#include <GpCore2/GpUtils/Types/Containers/GpContainersT.hpp>

namespace GPlatform {

class GpGeoFormatManager
{
public:
    CLASS_REMOVE_CTRS_MOVE_COPY(GpGeoFormatManager)
    CLASS_DD(GpGeoFormatManager)

protected:
                                    GpGeoFormatManager  (void) = default;

public:
    virtual                         ~GpGeoFormatManager (void) noexcept = default;

    virtual GpGeoShape::C::Vec::Val Read                (std::string_view aFileName) = 0;
    virtual void                    Write               (const GpGeoShape::C::Vec::Val& aShapes,
                                                         std::string_view               aFileName) = 0;
};

}// namespace  GPlatform
