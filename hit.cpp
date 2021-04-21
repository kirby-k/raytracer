#include "hit.h"
#include "materials.h"

hit::hit(double time, Point3D point, Vector3D normal, std::shared_ptr<material> m) 
    :time{time}, point{point}, normal{normal}, m{m} {}

std::ostream& operator<<(std::ostream& os, const hit& hit) {
    return os << "hit(time= " << hit.time << ", point= " << hit.point << ", normal= " << hit.normal << ", material= " << hit.m << ")";
}