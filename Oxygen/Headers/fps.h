// Oxygen - fps.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OXYGEN_FPS_H
#define OXYGEN_FPS_H
#pragma once

#include "glitter.h"

namespace oxygen {
    class fps {
      private:
        static double _timeLastFrame;
        static double _deltaTime;

      public:
        static double timeLastFrame() { return _timeLastFrame; }

        static double deltaTime() { return _deltaTime; }

        static void frame() {
            double time = glfwGetTime();
            _deltaTime = time - _timeLastFrame;
            _timeLastFrame = time;
        }

        static float calcFPS() { return 1.0f / _deltaTime; }
    };
}

#endif
