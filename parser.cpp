#include "parser.h"

using namespace std;

parser::parser(const std::string& filename) {
    ifstream in(filename);
    if (!in) {
        string msg{"Could not open file: " + filename};
        throw runtime_error(msg);
    }
    parse(in);
    verify();

}

camera parser::getCamera() {
    return cam;
}

world parser::getWorld() {
    return w;
}

Pixels parser::getPixels() {
    return pixels;
}

Pixels parser::getEmptyPixels() {
    return Pixels{pixels.width,pixels.height};
}

void removeLine(string& line) {
    line="";
}

void removeComment(string line) {
    auto i = line.find('#');
    if (i != string::npos) {
        line = line.substr(0,i);
    }
}

bool isWhitespace(string line) {
    return all_of(begin(line),end(line),::isspace);
}

bool isType(const string& line, const string& type) {
    return line.find(type) == 0;
}

bool isComment(string& line) {
    return line.find('#') == 0;
}

void parser::verify() {
    if (cam.aspect == -1) {
        throw runtime_error("No camera in file");
    }
    if (w.objects.empty()) {
        throw runtime_error("No spheres in file");
    }
    if (pixels.height == 0) {
        throw runtime_error("No pixels in file");
    }
    if (output == "") {
        throw runtime_error("No output file");
    }
    if (!foundRays) {
        throw runtime_error("No rays found\n");
    }
}

cParts parser::parseCamera(string line) {
    stringstream ss;
    ss << line;
    string type;
    Vector3D pos,target,up;
    double fov(-1),aspect(-1);
    char paren;
    ss >> type;
    ss >> paren;
    ss >> pos;
    ss >> paren >> paren;
    ss >> target;
    ss >> paren >> paren;
    ss >> up;
    ss >> paren;
    ss >> fov >> aspect;
    cParts cp{pos,target,up,fov,aspect};
    return cp;
}

double parser::parsePixels(string line) {
    stringstream ss;
    ss << line;
    string type;
    unsigned int w,h;
    ss >> type >> w >> h;
    pixels.set(w,h);
    return static_cast<double>(w)/static_cast<double>(h);
}

void parser::parseSphere(string line) {
    stringstream ss;
    ss << line;
    string type, matName;
    Point3D pos;
    char paren;
    std::shared_ptr<material> mat;
    double r;
    ss >> type >> paren >> pos >> paren >> r >> matName;
    auto itMat = map.find(matName);
    
    if (itMat != map.end()) {
        w.addSphere(pos,r,itMat->second);   
    }
    else {
        throw std::runtime_error("Cannot find material: " + matName);
    }
}

void parser::parseTriangle(string line, Vector3D dis, Vector3D size) {
    stringstream ss;
    ss << line;
    string type, matName;
    Point3D v1, v2, v3;
    char paren;
    std::shared_ptr<material> mat;
    ss >> type >> paren >> v1 >> paren >> paren >> v2 >> paren >> paren >> v3 >> paren >> matName;
    v1*=size;
    v2*=size;
    v3*=size;
    v1+=dis;
    v2+=dis;
    v3+=dis;

    
    auto itMat = map.find(matName);
    
    if (itMat != map.end()) {
        w.addTriangle(v1,v2,v3,itMat->second);   
    }
    else {
        throw std::runtime_error("Cannot find material: " + matName);
    }
}

void parser::parseMesh(string line) {
    stringstream ss;
    ss << line;
    Vector3D dis,size;
    double dsize;
    char paren;
    string filename, matName, type;
    std::shared_ptr<material> mat;
    ss >> type >> paren >> dis >> paren >> dsize >> filename >> matName;
    size = {dsize,dsize,dsize};
    auto itMat = map.find(matName);
    
    if (itMat != map.end()) {
        ifstream in(filename);
        string inLine;
        if (!in) {
            string msg{"Could not open file: " + filename};
            throw runtime_error(msg);
        }
        vector<string> vertices;
        while (getline(in,inLine)) {
            if (inLine == "vertices")
                continue;
            else if (inLine == "triangles")
                break;
            vertices.push_back(inLine);
        }
        while (getline(in,inLine)) {
            string tri = "triangle ";
            stringstream s;
            s << inLine;
            double t1,t2,t3;
            s >> t1 >> t2 >> t3;
            tri.append(vertices[t1]+" ");
            tri.append(vertices[t2]+" ");
            tri.append(vertices[t3]+" ");
            tri.append(matName);
            parseTriangle(tri, dis, size);
        }
    }
    else {
        throw std::runtime_error("Cannot find material: " + matName);
    }    
}

void parser::parseOutput(string line) {
    stringstream ss;
    ss << line;
    string type;
    ss >> type >> output;
}

void parser::parseMaterial(string line) {
    stringstream ss;
    ss << line;
    char paren;
    string material, name, kind, texture_name;
    Color col;
    double fuzz(2.0);
    bool isEmitting;
    ss >> material >> name >> kind >> texture_name >> paren >> col >> paren >> std::boolalpha >> isEmitting;

    if (texture_name == "solid") {
        tmap[texture_name] = std::make_shared<solid>(texture_name, col);
    }
    else if (texture_name == "check") {
        tmap[texture_name] = std::make_shared<check>(texture_name, col);
    }
    else if (texture_name == "gradient") {
        tmap[texture_name] = std::make_shared<gradient>(texture_name, col);
    }
    else {
        throw std::runtime_error("Unknown texture name: " + texture_name);
    }
    auto texture = tmap[texture_name];
    if (kind == "specular") {
        map[name] = make_shared<specular>(texture, isEmitting);
    }
    else if (kind == "diffuse") {
        map[name] = make_shared<diffuse>(texture, isEmitting);
    }
    else if (kind == "metal") {
        ss >> fuzz;
        map[name] = make_shared<metal>(texture, isEmitting, fuzz);
    }
    else if (kind == "unreal") {
        map[name] = make_shared<unreal>(texture, isEmitting);
    }
    else if (kind == "glass") {
        map[name] = make_shared<glass>(texture, isEmitting);
    }
    else {
        throw std::runtime_error("Unknown material: " + kind);
    }
}

void parser::parseRays(string line) {
    foundRays = false;
    stringstream ss;
    ss << line;
    string type;
    if (ss >> type >> depth >> samples) {
        foundRays = true;
    }
    else {
        throw std::runtime_error("Incorrect Parameters for ray\n");
    }
}

void parser::parse(ifstream& in) {
    string line;
    double aspect;
    tuple<Point3D,Point3D,Vector3D,double,double> cp;
    while (getline(in,line)) {
        if (isWhitespace(line)) {
            continue;
        }
        if (isComment(line)) {
            continue;
        }
        if(isType(line, "camera")) {
            cp = parseCamera(line);
        }
        else if (isType(line, "material")) {
            parseMaterial(line);
        }
        else if (isType(line, "pixels")) {
            aspect = parsePixels(line);
        }
        else if (isType(line, "sphere")) {
            parseSphere(line);
        }
        else if (isType(line, "triangle")) {
            parseTriangle(line);
        }
        else if (isType(line, "mesh")) {
            parseMesh(line);
        }
        else if (isType(line, "output")) {
            parseOutput(line);
        }
        else if (isType(line, "rays")) {
            parseRays(line);
        }
        else {
            throw runtime_error("Unknown type in line: " + line);
        }
    }
    camera c{get<0>(cp),get<1>(cp),get<2>(cp),get<3>(cp),aspect};
    cam = c;
}