#include <iostream>

#include "../include/Physics.h"
#include "../include/Body.h"

int main()
{
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

    constexpr double dt = 0.01;

    for (int i = 0; i < 10000000; ++i)
        physics.step(dt);
    return 0;
}