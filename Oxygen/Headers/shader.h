// Oxygen - shader.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Based off Glitter. https://github.com/Polytonic/Glitter

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

    class program {
      private:
        GLuint _handle;

      public:
        program() { _handle = glCreateProgram(); }

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

    class vao {
      private:
        GLuint _handle;

      public:
        vao() { glGenVertexArrays(1, &_handle); }

        void bind() { glBindVertexArray(_handle); }
    };
}

#endif
