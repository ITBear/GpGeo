#pragma once

#include "GpGeoFormatManager.hpp"

namespace GPlatform {

class GpGeoFormatManagerFactory
{
public:
    CLASS_DD(GpGeoFormatManagerFactory)

protected:
                                    GpGeoFormatManagerFactory   (void) noexcept = default;

public:
    virtual                         ~GpGeoFormatManagerFactory  (void) noexcept = default;

    virtual GpGeoFormatManager::SP  NewInstance                 (void) const = 0;
};

}//namespace GPlatform
