#include <iostream>
#include <cmath>

#include "util.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

// QUadratic solution for intersection of ray and sphere
double hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = r.origin() - center;
    auto a = r.direction().norm_squared();
    auto half_b = dot(r.direction(), oc);
    auto c = oc.norm_squared() - radius * radius;
    auto discrim = half_b * half_b - a * c; // if discriminant positive they intersect
    if (discrim < 0) return -1;
    return (-half_b - std::sqrt(discrim)) / a; // closer root
}

// Linear blend
// Colour red when hitting sphere
color ray_color(const ray& r, const hittable_list& world){
    const auto WHITE = color(1.0, 1.0, 1.0);
    const auto BLUE = color(0.5, 0.7, 1.0);
    hit_record hr;
    if (world.hit(r, 0, infinity, hr)){
        return (hr.normal + color(1)) * 0.5;
    }
    vec3 unit_direction = unit_vector(r.direction());
    // y is [-1, 1] t should be [0, 1]
    auto t = 0.5 * (unit_direction[1] + 1);
    return WHITE * (1 - t) + BLUE * t;
}

int main(){
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5)); // sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100)); // ground

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j){
        std::cerr << "Scanlines remaining " << image_height - j - 1 << '\n'; 
        for (int i = 0; i < image_width; ++i){
            auto x = double(i) / (image_width - 1);
            auto y = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + horizontal * x + vertical * y - origin);
            color pixel = ray_color(r, world);
            write_color(std::cout, pixel);
        }
    }
    std::cerr << "Done.\n";
}