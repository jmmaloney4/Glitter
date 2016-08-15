// Oxygen - texture.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OXYGEN_TEXTURE_H
#define OXYGEN_TEXTURE_H
#pragma once

#include "glitter.h"

namespace oxygen {
    class texture {
      private:
        GLuint _handle;
        int _width;
        int _height;
        int _comp;

      public:
        GLuint handle() { return _handle; }

        texture(const char* path, GLenum tex) {
            unsigned char* image =
                stbi_load(path, &_width, &_height, &_comp, STBI_rgb_alpha);

            if (image == nullptr) {
                throw(std::string("Failed to load texture"));
            }

            glGenTextures(1, &_handle);
            this->bind(tex);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, image);

            stbi_image_free(image);
        }

        ~texture() { glDeleteBuffers(1, &_handle); }

        void bind(GLenum tex) {
            glActiveTexture(tex);
            glBindTexture(GL_TEXTURE_2D, _handle);
        }
    };
}

#endif
