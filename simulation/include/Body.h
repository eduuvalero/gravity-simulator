#ifndef BODY_H
#define BODY_H

#include <cmath>
#include <iostream>
#include <algorithm>

struct Vector3d{
    double x, y, z;

    constexpr Vector3d operator+(const Vector3d& v) const { 
        return { x + v.x, y + v.y, z + v.z}; 
    }
    constexpr Vector3d operator-(const Vector3d& v) const { 
        return { x - v.x, y - v.y, z - v.z}; 
    }   

    constexpr Vector3d operator*(double k) const { 
        return {x*k, y*k, z*k}; 
    }

    constexpr Vector3d operator/(double k) const { 
        return {x/k, y/k, z/k}; 
    }

    constexpr Vector3d& operator+=(const Vector3d& v){ 
        x+=v.x; y+=v.y; z+=v.z; return *this; 
    }

    constexpr Vector3d& operator-=(const Vector3d& v){ 
        x-=v.x; y-=v.y; z-=v.z; return *this; 
    }

    constexpr Vector3d& operator/=(double k) { 
        x/=k; y/=k; z/=k; return *this; 
    }
    
    constexpr double dot(const Vector3d& v) const { 
        return x*v.x + y*v.y + z*v.z; 
    }

    constexpr double normSq() const { 
        return dot(*this); 
    }

    constexpr double norm() const { 
        return std::sqrt(normSq()); 
    }

    Vector3d componentWiseMin(const Vector3d& v){
        return {std::min(x, v.x), std::min(y, v.y), std::min(z, v.z)};
    }

    Vector3d componentWiseMax(const Vector3d& v){
        return {std::max(x, v.x), std::max(y, v.y), std::max(z, v.z)};
    }

    friend constexpr Vector3d operator*(double s, const Vector3d& v) noexcept {
        return v * s;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3d& v) noexcept {
        os << "[" << v.x << "," << v.y << "," << v.z << "]";
        return os; 
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