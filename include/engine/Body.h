#pragma once

#include <string>

#include "math/Vector3.h"

enum class BodyType{
    Star, Planet
};

struct Body{
    unsigned int id;
    bool alive = true;

    std::string name;
    BodyType type;

    double mass; 
    double radius;

    Vec3f color;

    Vec3d position;
    Vec3d velocity;
    Vec3d acceleration;

    Body() : id(nextID++) {}
    Body(BodyType type, double mass, double radius, const Vec3d& position, const Vec3d& velocity = {}) : 
        id(nextID++), type(type),mass(mass),radius(radius),position(position),velocity(velocity){}

private:
    inline static unsigned int nextID = 0;
};