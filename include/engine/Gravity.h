#pragma once

#include "Body.h"
#include "OctreeNode.h"
#include "math/Vector3.h"

class Gravity{
    private:
        Vec3d barnesHut(Body* body, OctreeNode* node);

        Vec3d calculateAccelerationFromMass(Body* body, double mass, const Vec3d& position);

        Vec3d calculateAccelerationBetweenBodies(Body* a, Body* b);

        bool shouldApproximate(Body* body, OctreeNode* node);
    public:
        Vec3d calculateAcceleration(Body* body, OctreeNode* root){
            return barnesHut(body, root);
        };
};
