#include "sphere.h"

sphere::sphere(Point3D center, double radius, std::shared_ptr<material> m1) 
    :center{center}, radius{radius}{
        m = m1;
    }

bool sphere::intersect(const ray& ray, double& time) const {
    Vector3D cp = center - ray.origin;
    double R = dot(ray.direction, cp); // t = R +/- h
    double q2 = dot(cp, cp) - R*R;
    if (q2 > radius*radius) return false; // leave if miss
    
    double h = std::sqrt(radius*radius - q2); //right trangle, pathagoreas 

    if ((R-h) > Constants::Epsilon) { // if time to hit is positive and far enough away (.0001)
        time = R-h;
        return true;
    }
    else if ((R+h) > Constants::Epsilon) { // time > epsilon, we're inside the sphere, time is positive and far enough away
        time = R + h;
        return true;
    }
    else { // surface of sphere is too close to camera
        return false;
    }
}

double sphere::where(const ray& ray) const {
    Vector3D cp = center - ray.origin;
    double R = dot(cp, ray.direction);
    double q2 = dot(cp, cp) - R*R;
    double q = sqrt(q2);
    return radius - q;
}

hit sphere::construct_hit(const ray& ray, double time) {
    Point3D point = ray.at(time);
    Vector3D normal = unit(point-center);
    return hit{time,point,normal, m};
}

std::pair<double,double> sphere::uv(const hit& hit) const {
    double theta = std::acos(hit.normal.z);
    double phi = std::atan2(hit.normal.y, hit.normal.x);
    double u = .5 + phi / (2*Constants::Pi);
    double v = theta / Constants::Pi;
    return{u,v};
}

void sphere::print() const {
    std::cout << "\nSphere(Center = " << center << " Radius = " << radius << "\n ";
}