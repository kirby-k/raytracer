#include "triangle.h"
#include "constants.h"

triangle::triangle() {}

triangle::triangle(Point3D v1, Point3D v2, Point3D v3, std::shared_ptr<material> m1)
    :vert1{v1},vert2{v2},vert3{v3} {
        edge1 = vert2 - vert1;
        edge2 = vert3 - vert1;
        m = m1;
        normal = unit(cross(edge1,edge2));
}

hit triangle::construct_hit(const ray& ray, double time) {
    Point3D point = ray.at(time);
    if (dot(ray.direction,normal) > 0) {
        return hit{time,point,-normal,m};
    }
    return hit{time,point,normal,m};
}

bool triangle::intersect(const ray& ray, double& time) const {
    Vector3D pvec = cross(ray.direction, edge2);
    double det = dot(edge1, pvec);
    if (det > -(Constants::Epsilon) && det < Constants::Epsilon)
        return false;
    double inv_det = 1.0 / det;

    Vector3D tvec = ray.origin - vert1;

    double u = dot(tvec, pvec) * inv_det;
    if (u < 0.0 || u > 1.0)
        return false;

    Vector3D qvec = cross(tvec,edge1);

    double v = dot(ray.direction,qvec) * inv_det;
    if (v < 0.0 || u + v > 1.0)
        return false;
    
    time = dot(edge2, qvec) * inv_det;
    if (time > Constants::Epsilon) {
        return true;
    }
    return false;
}

std::pair<double,double> triangle::uv(const hit& hit) const {
    Point3D p = hit.point - vert1;
    double u = dot(p, edge1) / norm(edge1);
    double v = dot(p, edge2) / norm(edge2);
    double mag = (u+v) / 2;
    return {u/mag,v/mag};
}

void triangle::print() const {
    std::cout << "V1: " << vert1 << " V2: " << vert2 << " V3: " << vert3 << " Material: "; m->print(); std::cout << "\n";
}