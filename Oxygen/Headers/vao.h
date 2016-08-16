// Oxygen - vao.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OXYGEN_VAO_H
#define OXYGEN_VAO_H
#pragma once

#include "glitter.h"

namespace oxygen {
    class vao {
      private:
        GLuint _handle;

      public:
        vao() { glGenVertexArrays(1, &_handle); }

        GLuint handle() { return _handle; }

        void bind() { glBindVertexArray(_handle); }
    };
}

#endif
