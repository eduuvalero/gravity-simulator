#include <iostream>

#include "engine/Physics.h"
#include "engine/Body.h"

#include "config/Config.h"

using namespace std;

int main(){
    Config::load("config/config.json");
    Physics physics;

    Body sun;
    sun.mass = 1000.0;
    sun.position = {0.0, 0.0, 0.0};
    sun.velocity = {0.0, 0.0, 0.0};

    Body earth;
    earth.mass = 1.0;
    earth.position = {20.0, 0.0, 0.0};
    earth.velocity = {0.0, 7.1, 0.0};

    Body moon;
    moon.mass = 0.0123;
    moon.position = {22.0, 0.0, 0.0};
    moon.velocity = {0.0, 8.0, 0.0};

    physics.addBody(&sun);
    physics.addBody(&earth);
    physics.addBody(&moon);

    const double dt = Config::simulation.dt;

    for (int i = 0; i < 1000000; ++i){
        physics.step(dt);
        cout << "Step " << i << ": Earth position: " << earth.position << ", Moon position: " << moon.position << std::endl;
    }
    return 0;
}