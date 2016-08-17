// Oxygen - player.h
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OXYGEN_PLAYER_H
#define OXYGEN_PLAYER_H
#pragma once

#include "glitter.h"

namespace oxygen {
    class player {
      private:
        static player* _instance;

        glm::mat4 position;

      public:
        player* instance() { return _instance; }
    };
}

#endif
