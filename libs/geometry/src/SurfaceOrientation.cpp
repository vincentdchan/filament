/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <geometry/SurfaceOrientation.h>

#include "geometry/TangentSpaceMesh.h"

#include <utils/Panic.h>
#include <utils/debug.h>

#include <math/mat3.h>
#include <math/norm.h>

#include <vector>

namespace filament {
namespace geometry {

using namespace filament::math;
using std::vector;
using Builder = SurfaceOrientation::Builder;

struct OrientationBuilderImpl {
    TangentSpaceMesh::Builder builder;
};

struct OrientationImpl {
    TangentSpaceMesh* tangentMesh;
};

Builder::Builder() noexcept : mImpl(new OrientationBuilderImpl) {}

Builder::~Builder() noexcept { delete mImpl; }

Builder::Builder(Builder&& that) noexcept {
    std::swap(mImpl, that.mImpl);
}

Builder& Builder::operator=(Builder&& that) noexcept {
    std::swap(mImpl, that.mImpl);
    return *this;
}

Builder& Builder::vertexCount(size_t vertexCount) noexcept {
    mImpl->builder.vertexCount(vertexCount);
    return *this;
}

Builder& Builder::normals(const float3* normals, size_t stride) noexcept {
    mImpl->builder.normals(normals, stride);
    return *this;
}

Builder& Builder::tangents(const float4* tangents, size_t stride) noexcept {
    mImpl->builder.tangents(tangents, stride);
    return *this;
}

Builder& Builder::uvs(const float2* uvs, size_t stride) noexcept {
    mImpl->builder.uvs(uvs, stride);
    return *this;
}

Builder& Builder::positions(const float3* positions, size_t stride) noexcept {
    mImpl->builder.positions(positions, stride);
    return *this;
}

Builder& Builder::triangleCount(size_t triangleCount) noexcept {
    mImpl->builder.triangleCount(triangleCount);
    return *this;
}

Builder& Builder::triangles(const uint3* triangles) noexcept {
    mImpl->builder.triangles(triangles);
    return *this;
}

Builder& Builder::triangles(const ushort3* triangles) noexcept {
    mImpl->builder.triangles(triangles);
    return *this;
}

SurfaceOrientation* Builder::build() {
    auto const impl = new OrientationImpl{ mImpl->builder.build() };
    return new SurfaceOrientation{ impl };
}

SurfaceOrientation::SurfaceOrientation(OrientationImpl* impl) noexcept : mImpl(impl) {}

SurfaceOrientation::~SurfaceOrientation() noexcept { delete mImpl; }

SurfaceOrientation::SurfaceOrientation(SurfaceOrientation&& that) noexcept {
    std::swap(mImpl, that.mImpl);
}

SurfaceOrientation& SurfaceOrientation::operator=(SurfaceOrientation&& that) noexcept {
    std::swap(mImpl, that.mImpl);
    return *this;
}

size_t SurfaceOrientation::getVertexCount() const noexcept {
    return mImpl->tangentMesh->getVertexCount();
}

void SurfaceOrientation::getQuats(quatf* out, size_t quatCount, size_t stride) const noexcept {
    return mImpl->tangentMesh->getQuats(out, stride);
}

void SurfaceOrientation::getQuats(short4* out, size_t quatCount, size_t stride) const noexcept {
    return mImpl->tangentMesh->getQuats(out, stride);
}

void SurfaceOrientation::getQuats(quath* out, size_t quatCount, size_t stride) const noexcept {
    return mImpl->tangentMesh->getQuats(out, stride);
}

} // namespace geometry
} // namespace filament
