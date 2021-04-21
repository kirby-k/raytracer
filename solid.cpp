#include "solid.h"

solid::solid(std::string name, Color color)
    :texture{name,color} {}

Color solid::uv(double,double) const {
    return color;
}