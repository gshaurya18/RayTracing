#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record{
    point3 p; // point where it hits a surface
    vec3 normal; // normal to the surface at the point
    double t; // t value for ray
};

class hittable{
    public:
        virtual bool hit(const ray&r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif