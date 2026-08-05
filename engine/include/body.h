#ifndef BODY_H
#define BODY_H

#include <cmath>

struct Vector3d{
    double x, y, z;

    constexpr Vector3d operator+(const Vector3d& o) const { 
        return { x + o.x, y + o.y, z + o.z}; 
    }
    constexpr Vector3d operator-(const Vector3d& o) const { 
        return { x - o.x, y - o.y, z - o.z}; 
    }   

    constexpr Vector3d operator*(double k) const { 
        return {x*k, y*k, z*k}; 
    }

    constexpr Vector3d operator/(double k) const { 
        return {x/k, y/k, z/k}; 
    }

    constexpr Vector3d& operator+=(const Vector3d& o) { 
        x+=o.x; y+=o.y; z+=o.z; return *this; 
    }

    constexpr Vector3d& operator-=(const Vector3d& o) { 
        x-=o.x; y-=o.y; z-=o.z; return *this; 
    }

    constexpr Vector3d& operator/=(double k) { 
        x/=k; y/=k; z/=k; return *this; 
    }
    
    constexpr double dot(const Vector3d& o) const { 
        return x*o.x + y*o.y + z*o.z; 
    }

    constexpr double normSq() const { 
        return dot(*this); 
    }

    constexpr double norm() const { 
        return std::sqrt(normSq()); 
    }

    friend constexpr Vector3d operator*(double s, const Vector3d& v) noexcept {
        return v * s;
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