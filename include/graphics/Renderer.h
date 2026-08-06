#pragma once

#include <vector>
#include "engine/Body.h"

class Renderer{
    private:
    public:
        void init();
        void clear();
        void draw(const std::vector<Body*>& bodies);
        void shutdown();
};