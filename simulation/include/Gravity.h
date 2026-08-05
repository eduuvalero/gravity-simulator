#ifndef GRAVITY_H
#define GRAVITY_H

#include "Body.h"
#include "Config.h"
#include "OctreeNode.h"

class Gravity{
    private:
        Vector3d barnesHut(Body* body, OctreeNode* node);

        Vector3d calculateForceFromMass(Body* body, double mass, const Vector3d& position);

        Vector3d calculateForceBetweenBodies(Body* a, Body* b);

        bool shouldApproximate(Body* body, OctreeNode* node);
    public:
        Vector3d calculateAcceleration(Body* body, OctreeNode* root){
            return barnesHut(body, root);
        };
};

#endif
