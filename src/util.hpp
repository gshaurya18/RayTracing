#ifndef UTIL_HPP
#define UTIL_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Aliases
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees){
    return degrees * pi / 180;
}

inline double random_double(double min=0.0, double max=1.0){
    // Random real in [min, max)
    static std::uniform_real_distribution<> dist(min, max);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return dist(gen);
}

// Clamp x to [min, max] range
inline double clamp(double x, double min, double max){
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double random_normal(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<> dist;
    return dist(gen);
}

// Project Headers
#include "ray.hpp"
#include "vec3.hpp"

#endif