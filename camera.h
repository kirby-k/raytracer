#pragma once

#include "vector3d.h"
#include "point3d.h"

class ray;

class camera {
public:
  camera();
  camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect);
  void operator=(camera);
  void print();
  void set(Point3D position, Point3D target, Vector3D up, double fov, double aspect);
  ray compute_ray(double u, double v) const;

  Point3D position, upper_left_corner, target;
  Vector3D horizontal, vertical;  
  double fov, aspect;
};
