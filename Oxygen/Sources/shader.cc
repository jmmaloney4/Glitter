// Oxygen - shader.cc
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Based off Glitter. https://github.com/Polytonic/Glitter

#include "shader.h"

void oxygen::handleShaderCompileErrors(GLint status, char* buffer) {
    if (status != GL_TRUE) {
        std::cout << "Compile Error (" << status << "): " << buffer
                  << std::endl;
    }
}
