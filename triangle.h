#pragma once

#include "object.h"

class triangle : public object {
    public:
        triangle();
        triangle(Point3D v1, Point3D v2, Point3D v3, std::shared_ptr<material> m1);
        hit construct_hit(const ray& ray, double time) override;
        bool intersect(const ray& ray, double& time) const override;
        std::pair<double,double> uv(const hit& hit) const override;
        void print() const override;
        Point3D vert1, vert2, vert3;
        Vector3D edge1, edge2, normal;
        
};