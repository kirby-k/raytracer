#include "specular.h"

specular::specular(std::shared_ptr<texture> texture, bool emitting) 
    :material{"specular", texture, emitting} {
}

ray specular::scatter(const ray& r, const hit& h) const {
    Vector3D reflected = reflect(r.direction, h.normal);
    return ray(h.point, reflected);
} 
