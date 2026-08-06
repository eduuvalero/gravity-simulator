#include "engine/Collisions.h"

namespace Collisions{
    bool checkCollision(const Body& a, const Body& b){
        Vector3d d = a.position - b.position;

        double distanceSq = d.normSq();
        double radiusSum = a.radius + b.radius;
        return distanceSq <= radiusSum * radiusSum;
    }

    void elasticCollision(Body& a, Body& b){
        Vector3d normal = b.position - a.position;

        double distance = normal.norm();

        if (distance < 1e-8){
            normal = {1, 0, 0};
        }
        else{
            normal /= distance;
        }

        Vector3d relativeVelocity = b.velocity - a.velocity;

        double velocityAlongNormal = relativeVelocity.dot(normal);

        if (velocityAlongNormal > 0)
            return;

        double restitution = 1.0;

        double impulse = -(1.0 + restitution) * velocityAlongNormal / (1.0 / a.mass + 1.0 / b.mass);

        Vector3d impulseVector = normal * impulse;

        a.velocity -= impulseVector / a.mass;
        b.velocity += impulseVector / b.mass;
    }

    void resolveCollision(Body& a, Body& b){
        if (!a.alive || !b.alive)
            return;

        if (a.type == Star && b.type == Star){
            a.mass += b.mass;

            a.radius = std::cbrt(a.radius * a.radius * a.radius + b.radius * b.radius * b.radius);

            b.alive = false;

            if(b.mass > a.mass)
            return;
        }

        if (a.type == Star){
            b.alive = false;
            return;
        }

        if (b.type == Star)
        {
            a.alive = false;
            return;
        }

        if (a.type == Asteroid && b.type != Asteroid){
            a.alive = false;
            return;
        }

        if (b.type == Asteroid && a.type != Asteroid){
            b.alive = false;
            return;
        }

        elasticCollision(a, b);
    }
};