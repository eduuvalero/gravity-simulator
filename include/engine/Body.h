#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include "math/Vector3.h"

enum class BodyType{
    Star, Planet
};

struct Body{
    unsigned int id;
    std::string name;
    BodyType type;
    bool alive = true;

    double mass; 
    double radius;

    Vec3f color;
    Vec3d position;
    Vec3d velocity;
    Vec3d acceleration;

    Body() : id(nextID++) {}
    Body(BodyType type, double mass, double radius, Vec3d position, Vec3d velocity = {0,0,0}): id(nextID++),
            type(type),mass(mass),radius(radius),position(position),velocity(velocity){}

private:
    inline static unsigned int nextID = 0;
};