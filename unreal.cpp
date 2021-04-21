#include "unreal.h"

unreal::unreal(std::shared_ptr<texture> texture, bool emitting) 
    :material{"Unreal", texture, emitting}
{}

ray unreal::scatter(const ray &r, const hit &h) const {
    //Vector3D scattered = cross(r.direction,h.normal);
    Vector3D scattered = r.direction*-1;
    return ray{h.point,scattered};
}