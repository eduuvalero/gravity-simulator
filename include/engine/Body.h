#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>

#include "Vector3d.h"

enum BodyType{
    Star, Planet, Moon, Asteroid
};

struct Body{
    unsigned int id;
    BodyType type;
    bool alive = true;

    double mass; 
    double radius;

    Vector3d position;
    Vector3d velocity;
    Vector3d acceleration;

    Body() : id(nextID++) {}
    Body(BodyType type, double mass, double radius, Vector3d position, Vector3d velocity = {0,0,0}): id(nextID++),
            type(type),mass(mass),radius(radius),position(position),velocity(velocity){}

private:
    inline static unsigned int nextID = 0;
};