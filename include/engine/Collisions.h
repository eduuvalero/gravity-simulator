#pragma once

#include <vector>

#include "Body.h"

namespace Collisions{
    bool checkCollision(const Body& a, const Body& b);
    void resolveCollision(Body& a, Body& b);
};