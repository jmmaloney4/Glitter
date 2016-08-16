// Oxygen - program.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OXYGEN_PROGRAM_H
#define OXYGEN_PROGRAM_H
#pragma once

#include "glitter.h"
#include "shader.h"

namespace oxygen {
    class program {
      private:
        GLuint _handle;

      public:
        program() { _handle = glCreateProgram(); }

        GLuint handle() { return _handle; }

        void addShader(shader s) { glAttachShader(_handle, s.handle()); }

        GLint link(char* err, GLint size) {
            glLinkProgram(_handle);

            GLint status;
            glGetProgramiv(_handle, GL_LINK_STATUS, &status);
            if (status != GL_TRUE) {
                glGetProgramInfoLog(_handle, size, NULL, err);
            }
            return status;
        }

        void use() { glUseProgram(_handle); }

        void setAttributeArray(const char* name, GLint size, GLenum type,
                               bool normalized, GLsizei stride,
                               const GLvoid* index) {
            GLint attrib = glGetAttribLocation(_handle, name);
            glEnableVertexAttribArray(attrib);
            glVertexAttribPointer(attrib, size, type, normalized, stride,
                                  index);
        }

        GLint getUniformLocation(const char* name) {
            return glGetUniformLocation(_handle, name);
        }
    };
}

#endif
