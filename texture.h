#pragma once
#include "color.h"
#include <string>
#include "ray.h"
#include "hit.h"
#include <iostream>


class texture {
    public:
        texture(std::string name, Color color);
        virtual Color uv(double u, double v) const = 0;
    //private:
        std::string name;
        Color color;
};