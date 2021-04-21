#include "diffuse.h"
#include "random.h"

diffuse::diffuse(std::shared_ptr<texture> texture, bool emitting)
    :material{"Diffuse", texture, emitting} 
{}

ray diffuse::scatter(const ray& r, const hit& h) const {
    Vector3D scattered = randomHemisphere(h.normal);
    return ray{h.point, scattered};
}