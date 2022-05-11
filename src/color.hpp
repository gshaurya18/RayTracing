#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void write_color(std::ostream& os, color pixel){
    // Write translated [0, 255] value
    const int ir = static_cast<int>(255.999 * pixel[0]);
    const int ig = static_cast<int>(255.999 * pixel[1]);
    const int ib = static_cast<int>(255.999 * pixel[2]);

    os << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif