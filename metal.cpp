#include "metal.h"
#include "random.h"
#include "specular.h"

metal::metal(std::shared_ptr<texture> texture, bool emitting, double fuzz) 
    :material{"Metal", texture, emitting, fuzz}
{}

ray metal::scatter(const ray &r, const hit &h) const {
    Vector3D specular = reflect(r.direction, h.normal);
    Vector3D diffuse = randomHemisphere(h.normal);
    specular *= 1+fuzz;
    diffuse *= 1-fuzz;
    return ray{h.point,specular+diffuse};
}

Vector3D metalScatter(Point3D p, double fuzz) {
    return p;
}