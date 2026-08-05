#include "engine/Physics.h"

#include <algorithm>

void Physics::addBody(Body* body){
    bodies_.push_back(body);
}

void Physics::buildTree(){
    Vector3d min = bodies_[0]->position;
    Vector3d max = bodies_[0]->position;

    for(Body* b : bodies_){
        min = min.componentWiseMin(b->position);
        max = max.componentWiseMax(b->position);
    }

    Vector3d center = (min + max) / 2.0;
    double size = std::max({max.x - min.x, max.y - min.y, max.z - min.z}) * 0.5;

    root_ = std::make_unique<OctreeNode>(center, size);

    for(Body* b : bodies_){
        root_->insert(b);
    }
}

void Physics::computeAccelerations(){
    for (Body* body : bodies_){
        body->acceleration = gravity_.calculateAcceleration(body, root_.get());
    }
}

void Physics::step(double dt){
    if(firstStep_){
        firstStep_ = false;
        buildTree();
        computeAccelerations();
    }

    integrator_.kick(bodies_, dt);
    integrator_.drift(bodies_, dt);

    buildTree();

    computeAccelerations();
    integrator_.kick(bodies_, dt);
};