// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2019 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "FilamentEntitiesMods.h"

#include <filament/MaterialInstance.h>

namespace open3d
{
namespace visualization
{

void FilamentMaterialModifier::Reset()
{
    // TODO: Print log or assert
    // assert(materialInstance == nullptr, "Previous material instance modifications are not finished!");

    materialInstance = nullptr;
    currentHandle = MaterialInstanceHandle::kBad;
}

void FilamentMaterialModifier::InitWithMaterialInstance(filament::MaterialInstance* aMaterialInstance, const MaterialInstanceHandle& id)
{
    // TODO: Print log or assert
    // assert(materialInstance == nullptr, "Previous material instance modifications are not finished!");

    materialInstance = aMaterialInstance;
    currentHandle = id;
}

MaterialModifier& FilamentMaterialModifier::SetParameter(const char* parameter, const float& value)
{
    if (materialInstance) {
        materialInstance->setParameter(parameter, value);
    }

    return *this;
}

MaterialModifier& FilamentMaterialModifier::SetColor(const char* parameter, const Eigen::Vector3f& value)
{
    if (materialInstance) {
        const auto color = filament::math::float3{value.x(), value.y(), value.z()};
        materialInstance->setParameter(parameter, filament::RgbType::sRGB, color);
    }

    return *this;
}

MaterialInstanceHandle FilamentMaterialModifier::Finish()
{
    auto res = currentHandle;

    materialInstance = nullptr;
    currentHandle = MaterialInstanceHandle::kBad;

    return res;
}

}
}