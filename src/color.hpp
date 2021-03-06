#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>
#include <cmath>

void write_color(std::ostream& os, color pixel, int samples_per_pixel){
    auto r = pixel[0];
    auto g = pixel[1];
    auto b = pixel[2];

    // Scale cummulative value by number of samples
    auto scale = 1.0 / samples_per_pixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    // Write translated [0, 255] value
    const int ir = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    const int ig = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    const int ib = static_cast<int>(256 * clamp(b, 0.0, 0.999));

    os << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif