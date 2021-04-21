#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "world.h"
#include "camera.h"
#include "pixels.h"
#include <tuple>
#include <map>
#include <algorithm>
#include <sstream>
#include "specular.h"
#include "diffuse.h"
#include "metal.h"
#include "unreal.h"
#include "texture.h"
#include "solid.h"
#include "check.h"
#include "gradient.h"
#include "glass.h"

class material;
class texture;

using cParts = std::tuple<Point3D,Point3D,Vector3D,double,double>;
using matMap = std::map<std::string,std::shared_ptr<material>>;
using texMap = std::map<std::string, std::shared_ptr<texture>>;

class parser {
    public:
        parser(const std::string& filename);
        camera getCamera();
        world getWorld();
        Pixels getPixels();
        Pixels getEmptyPixels();
        void parse(std::ifstream& in);
        cParts parseCamera(std::string line);
        void parseSphere(std::string line);
        void parseTriangle(std::string line, Vector3D dis = {0,0,0}, Vector3D size = {1,1,1});
        void parseMesh(std::string line);
        double parsePixels(std::string line);
        void parseOutput(std::string line);
        void parseMaterial(std::string line);
        void parse_texture(std::string line);
        void parseRays(std::string line);
        void verify();

        matMap map;
        texMap tmap;
        camera cam;
        world w;
        Pixels pixels;
        std::string output;
        int depth, samples;
        bool foundRays;
};