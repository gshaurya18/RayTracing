#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "util.hpp"
#include "hittable.hpp"

class material{
    public:
        virtual bool scatter(
            const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
        virtual ~material() { }
};

class lambertian: public material{
    color albedo;
    public:
        lambertian (const color& c): albedo(c) { }

        virtual bool scatter(
            const ray&, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            auto scatter_direction = rec.normal + random_unit_vector();
            // Degenerate scatter direction = 0,0,0
            if (scatter_direction.near_zero()) scatter_direction = rec.normal;
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
};

class metal: public material{
    color albedo;
    public:
        metal(const color& c): albedo(c) { }

        virtual bool scatter(
            const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return dot(scattered.direction(), rec.normal) > 0;
        }
};

#endif