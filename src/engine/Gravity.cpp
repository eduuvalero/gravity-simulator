#include "engine/Gravity.h"

#include <cmath>
#include "config/Config.h"

Vec3d Gravity::calculateAccelerationFromMass(Body* body, double mass, const Vec3d& position){
    Vec3d direction = position - body->position;

    double distanceSq = direction.normSq() + Config::physics.softening * Config::physics.softening;

    double factor = Config::physics.gravitationalConstant * mass / (distanceSq * std::sqrt(distanceSq));

    return direction * factor;
}

Vec3d Gravity::calculateAccelerationBetweenBodies(Body* a, Body* b){
    return calculateAccelerationFromMass(a, b->mass, b->position);
}

bool Gravity::shouldApproximate(Body* body, OctreeNode* node){
    double distance = (node->getCenterOfMass() - body->position).norm();

    double size = node->getHalfWidth() * 2.0;

    return (distance > 0 ? (size / distance) < Config::physics.barnesHutTheta : false);
};

Vec3d Gravity::barnesHut(Body* body, OctreeNode* node){
    Vec3d acceleration{0,0,0};

    if(node->getTotalMass() == 0){
        return acceleration;
    }

    if(node->isLeaf()){
        for(Body* other : node->getBodies()){
            if(other != body){
                acceleration += calculateAccelerationBetweenBodies(body, other);
            }
        }

        return acceleration;
    }

    if(shouldApproximate(body, node)){
        return calculateAccelerationFromMass(body, node->getTotalMass(), node->getCenterOfMass());
    }

    for(const auto& child : node->getChildren()){
        if(child){
            acceleration += barnesHut(body, child.get());
        }
    }

    return acceleration;
}
