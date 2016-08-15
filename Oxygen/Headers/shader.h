// Oxygen - shader.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OXYGEN_SHADER_H
#define OXYGEN_SHADER_H
#pragma once

#include "glitter.h"

namespace oxygen {
    class shader {
      private:
        GLuint _handle;

      public:
        shader(const char* src, GLenum type) {
            _handle = glCreateShader(type);
            glShaderSource(_handle, 1, &src, NULL);
        }

        GLint compile(char* err, GLint size) {
            glCompileShader(_handle);

            GLint status;
            glGetShaderiv(_handle, GL_COMPILE_STATUS, &status);
            if (status != GL_TRUE) {
                glGetShaderInfoLog(_handle, size, NULL, err);
            }

            return status;
        }

        GLuint handle() { return _handle; }
    };

    void handleShaderCompileErrors(GLint status, char* buffer);
}

#endif
