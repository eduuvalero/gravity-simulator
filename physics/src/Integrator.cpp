#include "../include/Integrator.h"

void Integrator::kick(std::vector<Body*>& bodies, double dt){
    for (Body* body : bodies){
        body->velocity += body->acceleration * (dt * 0.5);
    }
}

void Integrator::drift(std::vector<Body*>& bodies, double dt){
    for (Body* body : bodies){
        body->position += body->velocity * dt;
    }
}