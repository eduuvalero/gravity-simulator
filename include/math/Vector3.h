#pragma once

#include <algorithm>
#include <iostream>


template<typename T>
struct Vector3{
    T x, y, z;

    Vector3() = default;
    Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

    constexpr Vector3<T> operator+(const Vector3<T>& v) const { 
        return { x + v.x, y + v.y, z + v.z}; 
    }
    constexpr Vector3<T> operator-(const Vector3<T>& v) const { 
        return { x - v.x, y - v.y, z - v.z}; 
    }   

    constexpr Vector3<T> operator*(T k) const { 
        return {x*k, y*k, z*k}; 
    }

    constexpr Vector3<T> operator/(T k) const { 
        return {x/k, y/k, z/k}; 
    }

    constexpr Vector3<T>& operator+=(const Vector3<T>& v){ 
        x+=v.x; y+=v.y; z+=v.z; return *this; 
    }

    constexpr Vector3<T>& operator-=(const Vector3<T>& v){ 
        x-=v.x; y-=v.y; z-=v.z; return *this; 
    }

    constexpr Vector3<T>& operator/=(T k) { 
        x/=k; y/=k; z/=k; return *this; 
    }
    
    constexpr double dot(const Vector3<T>& v) const { 
        return x*v.x + y*v.y + z*v.z; 
    }

    constexpr double normSq() const { 
        return dot(*this); 
    }

    double norm() const { 
        return std::sqrt(normSq()); 
    }

    Vector3<T> componentWiseMin(const Vector3<T>& v){
        return {std::min(x, v.x), std::min(y, v.y), std::min(z, v.z)};
    }

    Vector3<T> componentWiseMax(const Vector3<T>& v){
        return {std::max(x, v.x), std::max(y, v.y), std::max(z, v.z)};
    }

    friend constexpr Vector3<T> operator*(T s, const Vector3<T>& v) noexcept {
        return v * s;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) noexcept {
        os << "[" << v.x << "," << v.y << "," << v.z << "]";
        return os; 
    }
};

using Vec3d = Vector3<double>;      
using Vec3f = Vector3<float>;
using Vec3i = Vector3<int>;