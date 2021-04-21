#include <iostream>
#include "ray.h"
#include "vector3d.h"
#include "point3d.h"
#include "sphere.h"
#include "pixels.h"
#include "camera.h"
#include "world.h"
#include "parser.h"
#include "materials.h"
#include "texture.h"
#include "random.h"
#include <chrono>
#include <iomanip>
#include <mpi.h>

void trace(world, camera, Pixels&, int, int, int, int);
Color rTrace(world&, ray&, double);
void printProgress(long long rayNum, long long totalRays, int num_processes);

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    
    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);    

    parser p{"input.txt"};
    int depth{p.depth}, samples{p.samples};
    
    Pixels pix{p.getPixels()};
    camera cam{p.getCamera()};
    world wor{p.getWorld()};

    trace(wor,cam,pix,depth,samples,rank, num_processes);
    std::vector<double> sendPix;
    std::vector<double> recvPix;

    if (rank == 0) {
        recvPix.resize(pix.values.size() * num_processes * 3);
    }
    for (auto pix_color : pix.values) {
        double xCol = pix_color.x;
        double yCol = pix_color.y;
        double zCol = pix_color.z;
        sendPix.push_back(xCol);
        sendPix.push_back(yCol);
        sendPix.push_back(zCol);
    }

    MPI_Gather(sendPix.data(), sendPix.size(), MPI_DOUBLE, recvPix.data(), sendPix.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {   
        std::vector<Pixels> images;
        Pixels tmpPix = p.getEmptyPixels();
        std::vector<double> tmp;
        std::vector<Color> c;
        int count{0};
        for (auto dCol : recvPix) {
            tmp.push_back(dCol);
            count++;
            if (count % 3 == 0) {
                c.push_back(Color{tmp[0],tmp[1],tmp[2]});
                tmp.clear();
            }
            if (count % sendPix.size() == 0) {
                double colorCount{0};
               for (int row = 0; row < pix.height; row++) {
                    for (int col = 0; col < pix.width; col++) {
                        tmpPix(row,col) = c[colorCount];
                        colorCount++;
                    }
               }
                c.clear();
                images.push_back(tmpPix);
                tmpPix = p.getEmptyPixels();
            }
        }
        for (int row = 0; row < pix.height; row++) {
            for (int col = 0; col < pix.width; col++) {
                for (int i = 1; i < num_processes; i++) {
                    pix(row,col) += images[i](row,col);
                }
                pix(row,col) /= num_processes;
            }            
        }
        pix.save_png(p.output);
    }
    MPI_Finalize();
    if (rank == 0)
        std::cout << "\n\nUsed " << num_processes << " threads\nWrote to file: " << p.output << "\n\n";
    return 0;
}

void trace(world w, camera c, Pixels& p, int depth, int samples, int rank, int num_processes) {
    const long long raysTotal = p.width * p.height * static_cast<long long>(samples);
    long long rayNum = 0;
    if (rank == 0) {
        printProgress(rayNum,raysTotal,num_processes);
    }

    for (int row = 0; row < p.height; row++) {
        for (int col = 0; col < p.width; col++) {
            Color tmp{0,0,0};
            for (int s = 0; s < samples; s++) {
                double y = (row + randomDouble()) / static_cast<double>(p.height-1);
                double x = (col + randomDouble()) / static_cast<double>(p.width-1);
                ray r = c.compute_ray(x,y);
                p(row,col) += rTrace(w,r,depth);

                if (rank == 0) {
                    ++rayNum;
                    if (rayNum % (raysTotal / 100) == 0) {
                        printProgress(rayNum, raysTotal,num_processes);
                    }           
                }
            }
            p(row,col) /= samples;
        }    
    }
}

Color rTrace(world& w, ray& r, double depth) {
    if (depth == 0) {
        return black;
    }
    else {
        auto [time, nearest] = w.nearest(r);
        if (nearest) {
            hit h = nearest->construct_hit(r,time);
            std::shared_ptr<material> material = h.m;
            if (material->isEmitting) {
                return material->m_texture->color;
            }
            else {
                ray scattered = material->scatter(r,h);
                auto [u,v] = nearest->uv(h);
                return rTrace(w,scattered,depth-1) * material->m_texture->uv(u,v);
            }
        }
        else {
            return black; //sky
        }
    }
}

void printProgress(long long rayNum, long long totalRays, int num_processes) {
    auto width = std::to_string(totalRays).length() + 4;
    std::cout.imbue(std::locale(""));
    int percent = std::round(static_cast<double>(rayNum) / totalRays * 100);
    std::cout << "\rProgress: " << std::setw(3) << percent << "% ";
    std::cout << std::setw(width) << rayNum*num_processes << "/" << totalRays*num_processes << " rays";
    std::cout << std::flush;
}