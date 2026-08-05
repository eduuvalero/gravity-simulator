#pragma once
#include <vector>

#include "Body.h"
#include "Gravity.h"
#include "OctreeNode.h"

class Integrator{
    public:
        void kick(std::vector<Body*>& bodies_, double dt);
        void drift(std::vector<Body*>& bodies_, double dt);
};
