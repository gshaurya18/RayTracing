#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record{
    point3 p; // point where it hits a surface
    vec3 normal; // normal to the surface at the point
    double t; // t value for ray
    bool front_face; // Determine ray hitting front or back at time of geometric intersection
    // true if ray is outside the sphere
    // Normal always points out
    // if ray intersects from inside they are same directions
    // if ray comes from outside they are opposite direction
    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        normal = dot(r.direction(), outward_normal) < 0 ? outward_normal : -outward_normal; 
    }
};

class hittable{
    public:
        virtual bool hit(const ray&r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif