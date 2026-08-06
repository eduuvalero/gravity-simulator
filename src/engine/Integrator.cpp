#include "engine/Integrator.h"

void Integrator::kick(std::vector<Body*>& bodies, double dt){
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        bodies[i]->velocity += bodies[i]->acceleration * (dt * 0.5);
    }
}

void Integrator::drift(std::vector<Body*>& bodies, double dt){
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        bodies[i]->position += bodies[i]->velocity * dt;
    }
}