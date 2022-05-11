#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class ray{
    point3 orig;
    vec3 dir;
    public:
        ray() {}

        ray (const point3& origin_in, const vec3& dir_in) :
            orig{origin_in}, dir{dir_in} { } 
        
        point3 origin() const {return orig;}
        vec3 direction() const {return dir;}

        // r(t) = a + b * t
        point3 at(double t) const{
            return orig + dir * t;
        }

};

#endif