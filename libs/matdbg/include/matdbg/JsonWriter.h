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

#ifndef MATDBG_JSONWRITER_H
#define MATDBG_JSONWRITER_H

#include <filaflat/ChunkContainer.h>

#include <backend/DriverEnums.h>

#include <utils/CString.h>

#include "ShaderInfo.h"

namespace filament {
namespace matdbg {

// This class generates portions of JSON messages that are sent to the web client.
// Note that some portions of these JSON strings are generated by directly in DebugServer,
// as well as CommonWriter.
class JsonWriter {
public:

    // Retrieves the most recently generated string.
    const char* getJsonString() const;
    size_t getJsonSize() const;

    // Generates a JSON string describing the given material.
    bool writeMaterialInfo(const filaflat::ChunkContainer& package);

    // Generates a JSON string describing the currently active variants.
    //
    // The array is of the form [ backend, shaderIndex0, shaderIndex1, ... ] where each
    // shader index is an active variant. Each bit in the activeVariants bitmask
    // represents one of the possible variant combinations.
    bool writeActiveInfo(const filaflat::ChunkContainer& package, backend::Backend backend,
            VariantList activeVariants);

private:
    utils::CString mJsonString;
};

} // namespace matdbg
} // namespace filament

#endif  // MATDBG_JSONWRITER_H
