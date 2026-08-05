#ifndef BODY_H
#define BODY_H

#include <cmath>

struct Vector3d{
    double x, y, z;

    Vector3d operator+(const Vector3d& o) const { return { x + o.x, y + o.y, z + o.z}; }
    Vector3d operator-(const Vector3d& o) const { return { x - o.x, y - o.y, z - o.z}; }
    Vector3d operator*(double s) const { return {x*s, y*s, z*s}; }
    Vector3d operator/(double s) const { return {x/s, y/s, z/s}; }

    Vector3d& operator+=(const Vector3d& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }
    Vector3d& operator-=(const Vector3d& o) { x-=o.x; y-=o.y; z-=o.z; return *this; }
    Vector3d& operator/=(double s) { x/=s; y/=s; z/=s; return *this; }
    
    double dot(const Vector3d& o) const { return x*o.x + y*o.y + z*o.z; }
    double normSq() const { return dot(*this); }
    double norm() const { return std::sqrt(normSq()); }

    Vector3d normalized() const {
        double n = norm();
        return (n > 0) ? (*this) / n : Vector3d{0, 0, 0};
    }
};

struct Body{
    double mass; 
    double radius;
    Vector3d position;
    Vector3d velocity;
    Vector3d acceleration;
};

#endif