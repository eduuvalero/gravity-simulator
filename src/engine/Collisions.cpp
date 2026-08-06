#include "engine/Collisions.h"

#include <cmath>

namespace Collisions{
    bool checkCollision(const Body& a, const Body& b){
        Vector3d d = a.position - b.position;

        double distanceSq = d.normSq();
        double radiusSum = a.radius + b.radius;
        return distanceSq <= radiusSum * radiusSum;
    }

    void separateBodies(Body& a, Body& b){
        Vector3d direction = b.position - a.position;

        double distance = direction.norm();

        if(distance < 1e-8)
            return;

        double overlap = a.radius + b.radius - distance;

        if(overlap > 0){
            Vector3d normal = direction / distance;

            a.position -= normal * (overlap * 0.5);
            b.position += normal * (overlap * 0.5);
        }
    }

    void elasticCollision(Body& a, Body& b){
        
        separateBodies(a,b);

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
        if (a.type == Star && b.type == Star){
            Body* bigger = &a;
            Body* smaller = &b;

            if (b.mass > a.mass){
                bigger = &b;
                smaller = &a;
            }


            bigger->radius = std::cbrt(
                bigger->radius * bigger->radius * bigger->radius +
                smaller->radius * smaller->radius * smaller->radius
            );

            bigger->velocity = (bigger->velocity * bigger->mass + smaller->velocity * smaller ->mass) / (bigger->mass + smaller->mass);

            bigger->mass += smaller->mass;

            smaller->alive = false;

            return;
        }

        if (a.type == Star){
            a.mass += b.mass;
            b.alive = false;
            return;
        }

        if (b.type == Star){
            b.mass += a.mass;
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