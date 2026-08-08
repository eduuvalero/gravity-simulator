#pragma once

#include <vector>
#include <memory>

#include "Body.h"
#include "Gravity.h"
#include "OctreeNode.h"
#include "Integrator.h"

class Physics{
    private:
        std::vector<Body> bodies_;
        Gravity gravity_;
        std::unique_ptr<OctreeNode> root_;
        Integrator integrator_;
        bool firstStep_ = true;

        void buildTree();
        void computeAccelerations();
        void checkCollisions();
        void removeDeadBodies();
    public:
        void addBody(Body body);
        void addBodies(std::vector<Body> bodies);
        void importBodies(const std::string& path);
        void step(double dt);
};
