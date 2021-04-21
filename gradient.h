#pragma once
#include "texture.h"
class gradient : public texture {
    public:
        gradient(std::string name, Color color);
        Color uv(double u, double v) const override;
        
};