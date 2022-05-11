#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>
#include <cmath>
#include <cassert>
#include <array>

// Class that contains a triple of objects. Used for rgb color, 3d points etc.
class vec3{
    std::array<double, 3> arr;
    public:
        vec3(): arr{0, 0, 0} { }

        vec3(double d) : arr{d, d, d} { }

        vec3(double arr0, double arr1, double arr2) : arr{arr0, arr1, arr2} { }

        // Index into vec3 to get or set values
        double operator[](unsigned int i) const {
            assert(i < 3);
            return arr[i];
        }

        double& operator[](unsigned int i) {
            assert(i < 3);
            return arr[i];
        }

        // A new vec3 object with opposite signs for members
        vec3 operator-() const {
            return vec3(-arr[0], -arr[1], -arr[2]);
        }

        // Element-wise operations
        vec3& operator+=(const vec3 &other){
            arr[0] += other.arr[0];
            arr[1] += other.arr[1];
            arr[2] += other.arr[2];
            return *this;
        }

        vec3& operator*=(const double d){
            arr[0] *= d;
            arr[1] *= d;
            arr[2] *= d;
            return *this;
        }

        vec3& operator/=(const double d){
            return *this *= (1 / d);
        }

        // Squared l2-norm of vector
        double norm_squared() const{
            return arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2];
        }

        double norm() const{
            return std::sqrt(norm_squared());
        }

};

// Type aliases for vec3
using point3 = vec3; // point in 3D space
using color = vec3; // RGB color

#endif