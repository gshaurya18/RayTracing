#include <iostream>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"

// Linear blend
color ray_color(const ray& r){
    const auto WHITE = color(1.0, 1.0, 1.0);
    const auto BLUE = color(0.5, 0.7, 1.0);
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
            color pixel = ray_color(r);
            write_color(std::cout, pixel);
        }
    }
    std::cerr << "Done.\n";
}