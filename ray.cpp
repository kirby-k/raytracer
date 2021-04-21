#include "ray.h"

ray::ray(Vector3D origin, Vector3D direction) 
:origin{origin}, direction{unit(direction)} {}

Point3D ray::at(double t) const {
    return origin + direction * t;
}

std::ostream& operator<<(std::ostream& os, const ray& ray) {
    os << "ray(origin=" << ray.origin << " , direction=" << ray.direction << ")";
    return os;
}