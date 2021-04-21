#pragma once

class Vector3D;

double randomDouble(); // 0.0 - 1.0
double randomDouble(double min, double max);

Vector3D randomUnitVector();
Vector3D randomHemisphere(const Vector3D&);