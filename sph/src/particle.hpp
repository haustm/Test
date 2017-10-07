#pragma once

#include <Eigen/Dense>
#include <vector>

using namespace Eigen;

class Frame;

class Particle
{
    public:

        Vector3d pos;
        Vector3d f;
        Vector3d vel;
        int id;

        std::vector<Particle*> neighbours;
        Frame* mother;

        double mass;
        double rho_0, rho, ca, gamma;

        void move(double dt);

        void calcForces();
        void calcP();
        void calcRho();



    Particle(Frame* parent)
    {
        mass = 1000;
        rho_0 = 1000;
        rho = 0;
        ca = 100;
        gamma = 7;
        vel << 0,0,0;
        this->mother = parent;

        this->calcForces();
    }        
};
