#include "world.h"
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "materials.h"

world::world() {}

void world::addSphere(Point3D center, double radius, std::shared_ptr<material> m) {
    objects.push_back(std::make_shared<sphere>(center,radius,m));
}

void world::addTriangle(Point3D v1, Point3D v2, Point3D v3, std::shared_ptr<material> m) {
    objects.push_back(std::make_shared<triangle>(v1,v2,v3,m));
}

Nearest world::nearest(const ray& ray) const {
    double time = Constants::Infinity;
    std::shared_ptr<object> nearest = nullptr;
    for (auto objects : objects) {
        double t;
        if (objects->intersect(ray,t) && (t < time)) {
            time = t;
            nearest = objects;
        }
    }
    return {time, nearest};
}