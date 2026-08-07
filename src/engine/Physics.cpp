#include "engine/Physics.h"

#include <algorithm>

#include "engine/Collisions.h"

void Physics::addBody(Body* body){
    bodies_.push_back(body);
}

void Physics::buildTree(){
    if (bodies_.empty()) {
        root_.reset();
        return;
    }

    Vec3d min = bodies_[0]->position;
    Vec3d max = bodies_[0]->position;

    for(Body* b : bodies_){
        min = min.componentWiseMin(b->position);
        max = max.componentWiseMax(b->position);
    }

    Vec3d center = (min + max) / 2.0;
    double size = std::max({max.x - min.x, max.y - min.y, max.z - min.z}) * 0.5;
    size = std::max(size, 1e-6);

    root_ = std::make_unique<OctreeNode>(center, size);

    for(Body* b : bodies_){
        root_->insert(b);
    }
}

void Physics::computeAccelerations(){
    if (!root_) {
        return;
    }

    #pragma omp parallel for schedule(dynamic)
    for (std::size_t i = 0; i < bodies_.size(); ++i) {
        bodies_[i]->acceleration = gravity_.calculateAcceleration(bodies_[i], root_.get());
    }
}

void Physics::checkCollisions(){
    for (Body* body : bodies_){
        if (!body->alive)
            continue;

        std::vector<Body*> nearby;

        root_->querySphere(body->position, body->radius, nearby);


        for (Body* other : nearby){
            if (body == other)
                continue;

            if (body > other)
                continue;

            if (!other->alive)
                continue;

            if (Collisions::checkCollision(*body, *other)){
                Collisions::resolveCollision(*body, *other);
            }
        }
    }
}

void Physics::removeDeadBodies(){
        bodies_.erase(
        std::remove_if(bodies_.begin(), bodies_.end(), [](Body* body){
                return !body->alive;
            }
        ),
        bodies_.end()
    );
};

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

    checkCollisions();
    removeDeadBodies();
};