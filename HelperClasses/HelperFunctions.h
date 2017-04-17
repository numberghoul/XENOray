#pragma once
#include "Vector2.h"
#include "../Game/Game.h"

Vector2<int> Raycast(Vector2<int> &rayPos, Vector2<double> &rayDir, int &hit, int &side);
