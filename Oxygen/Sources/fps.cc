// Oxygen - fps.cc
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "fps.h"

using namespace oxygen;

double fps::_timeLastFrame = 0.0;
double fps::_deltaTime = 0.0;
