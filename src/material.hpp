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
    double fuzz;
    public:
        metal(const color& c, double f): albedo(c), fuzz(f < 1 ? f : 1) { }

        virtual bool scatter(
            const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + random_in_unit_sphere() * fuzz);
            attenuation = albedo;
            return dot(scattered.direction(), rec.normal) > 0;
        }
};

class dielectric: public material{
    double ri; // refractive index

    static double reflectance(double cosine, double ref_idx){
        // Use schlik's approximation for reflectance
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
    public:
        dielectric(double r): ri(r) { }
        
        virtual bool scatter(
            const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            attenuation = color(1);
            double refraction_ratio = rec.front_face ? (1.0 / ri) : ri;

            vec3 unit_direction = unit_vector(ray_in.direction());
            double cos_t = std::fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_t = std::sqrt(1 - cos_t * cos_t);

            bool cannot_refract = (refraction_ratio *  sin_t > 1.0);
            vec3 direction;

            if (cannot_refract || reflectance(cos_t, refraction_ratio) > random_double()){
                direction = reflect(unit_direction, rec.normal);
            }
            else{
                direction = refract(unit_direction, rec.normal, refraction_ratio);
            }

            scattered = ray(rec.p, direction);
            return true;
        }

};

#endif