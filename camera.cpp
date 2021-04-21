/*#include "camera.h"

camera::camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect) :position{position} {
    Vector3D w = unit(position - target);
    Vector3D u = unit(cross(up, w));
    Vector3D v = cross(w, u);

    double theta = fov * Constants::Pi / 180;
    double viewport_height = 2 * std::tan(theta / 2);
    double viewport_width = viewport_height * aspect;
    horiz = viewport_width * u;
    vert = viewport_height * v;
    Point3D image_center = position - w;
    upperLeft = image_center - 0.5 * (horiz - vert);
}
ray camera::compute_ray(double s, double t) const {
    Point3D point = upperLeft + s*horiz - t*vert;
    Vector3D direction = point - position;
    return ray{position, direction};
}   */

#include "camera.h"
#include "ray.h"
#include "constants.h"
#include <cmath>

camera::camera() :aspect{-1}{
}

camera::camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect)
  :position{position}, target{target}, fov{fov}, aspect{aspect} {
  // calculate camera coordinates

  Vector3D w = unit(position - target);
  
  Vector3D u = unit(cross(up, w));
  
  Vector3D v = cross(w, u);

  double theta = fov * Constants::Pi / 180;
  double viewport_height = 2 * std::tan(theta / 2.0);
  double viewport_width = viewport_height * aspect;
  horizontal = viewport_width * u;
  vertical = viewport_height * v;
  Vector3D image_center = position - w;
  upper_left_corner = image_center - 0.5 * (horizontal - vertical);
}

void camera::operator=(camera c) {
  position = c.position;
  upper_left_corner = c.upper_left_corner;
  target = c.target;
  horizontal = c.horizontal;
  vertical = c.vertical;
  fov = c.fov;
  aspect = c.aspect;
}

void camera::print() { 
  std::cout << "Camera(Position = " << position << " Target = " << target << " Fov = " << fov << " Aspect = " << aspect;
}

void camera::set(Point3D position, Point3D target, Vector3D up, double fov, double aspect) {
  std::cout << position << " " << target << " " << up << " " << fov << " " << aspect << "\n";
  Vector3D w = unit(position - target);  
  Vector3D u = unit(cross(up, w));
  Vector3D v = cross(w, u);
  double theta = fov * Constants::Pi / 180;
  double viewport_height = 2 * std::tan(theta / 2.0);
  double viewport_width = viewport_height * aspect;
  std::cout << "viewport: " << viewport_width << "\n u: " << u << "\n";
  exit(1);
  horizontal = viewport_width * u;
  exit(1);
  vertical = viewport_height * v;
  Vector3D image_center = position - w;
  upper_left_corner = image_center - 0.5 * (horizontal - vertical);  
}

ray camera::compute_ray(double u, double v) const {
  Vector3D point = upper_left_corner + u * horizontal - v * vertical;
  Vector3D direction = point - position;
  return ray{position, direction};
}