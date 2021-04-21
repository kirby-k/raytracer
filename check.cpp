#include "check.h"

check::check(std::string name, Color color) 
:texture{name,color} {}

Color check::uv(double u, double v) const {
    int U = static_cast<int>(u*12) % 2;
    int V = static_cast<int>(v*6) % 2;
    if ((U + V) % 2 == 0) {
        return color;
    }
    else {
        return black;
    }
}