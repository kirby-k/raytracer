#include "glass.h"

glass::glass(std::shared_ptr<texture> texture, bool emitting) 
    :material{"glass", texture, emitting} {
}

ray glass::scatter(const ray& r, const hit& h) const {
    auto direction = r.direction;
    auto normal = h.normal;
    double n1 = 1.0;
    double n2 = 1.5;
    if (dot(direction,normal) > 0) {
        normal *= -1;
        std::swap(n1,n2);
    }
    double cos_theta = -dot(direction,normal);
    double prob = schlick(cos_theta, n1/n2);

    if (randomDouble() < prob) {
        auto reflected = reflect(direction,normal);
        return ray{h.point, reflected};
    }
    else {
        auto refracted = refract(direction,normal,n1/n2);
        return ray{h.point, refracted};
    }
} 
