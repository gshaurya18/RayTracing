#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include <cmath>

class sphere: public hittable{
    point3 center;
    double radius;

    public:
        sphere(point3 center_in, double r) :
            center(center_in), radius(r) { }
        
        // Set hit record and return wether hit or not
        // hit record undefined if false returned
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override{
            vec3 oc = r.origin() - center;
            auto a = r.direction().norm_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.norm_squared() - radius * radius;

            auto discriminant = half_b * half_b - a * c;
            if (discriminant < 0) return false;
            double sqrtd = std::sqrt(discriminant);

            auto root = (-half_b - sqrtd) / a;

            // this root out of range; check other
            if (root < t_min || root > t_max){
                root = (-half_b + sqrtd) / a;
                if (root < t_min || root > t_max) return false; // no solution in range
            }

            rec.t = root;
            rec.p = r.at(root);
            rec.normal = (rec.p - center) / radius;

            return true;
        }
};

#endif