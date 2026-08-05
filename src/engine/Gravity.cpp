#include "engine/Gravity.h"
#include "config/config.h"

#include <cmath>

Vector3d Gravity::calculateForceFromMass(Body* body, double mass, const Vector3d& position){
    Vector3d direction = position - body->position;

    double distanceSq = direction.normSq() + Config::physics.softening * Config::physics.softening;

    double factor = Config::physics.gravitationalConstant * mass / (distanceSq * std::sqrt(distanceSq));

    return direction * factor;
}

Vector3d Gravity::calculateForceBetweenBodies(Body* a, Body* b){
    return calculateForceFromMass(a, b->mass, b->position);
}

bool Gravity::shouldApproximate(Body* body, OctreeNode* node){
    double distance = (node->getCenterOfMass() - body->position).norm();

    double size = node->getHalfWidth() * 2.0;

    return (size / distance) < Config::physics.barnesHutTheta;
};

Vector3d Gravity::barnesHut(Body* body, OctreeNode* node){
    Vector3d acceleration{0,0,0};

    if(node->getTotalMass() == 0){
        return acceleration;
    }

    if(node->isLeaf()){
        for(Body* other : node->getBodies()){
            if(other != body){
                acceleration += calculateForceBetweenBodies(body, other);
            }
        }

        return acceleration;
    }

    if(shouldApproximate(body, node)){
        return calculateForceFromMass(body, node->getTotalMass(), node->getCenterOfMass());
    }

    for(const auto& child : node->getChildren()){
        if(child){
            acceleration += barnesHut(body, child.get());
        }
    }

    return acceleration;
}
