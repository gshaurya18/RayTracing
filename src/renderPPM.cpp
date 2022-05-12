#include <iostream>
#include <cmath>

#include "util.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"

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
    const int samples_per_pixel = 100;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5)); // sphere
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100)); // ground

    // Camera
    camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j){
        std::cerr << "Scanlines remaining " << j << '\n'; 
        for (int i = 0; i < image_width; ++i){
            auto pixel = color(0);
            for (int s = 0; s < samples_per_pixel; ++s){
                auto x = (i + random_double()) / (image_width - 1);
                auto y = (j + random_double()) / (image_height - 1);
                auto r = cam.get_ray(x, y);
                pixel += ray_color(r, world);
            }
            write_color(std::cout, pixel, samples_per_pixel);
        }
    }
    std::cerr << "Done.\n";
}