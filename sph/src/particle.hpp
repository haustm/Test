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
        double press;

        void move(double dt);

        void calcForces();
        void calcP();
        void moveRho();
        void calcRho();



    Particle(Frame* parent)
    {
        mass = 1.0;
        rho_0 = 25.0;
        rho = 25.0;
        press = 0.1;
        ca = 0.010;
        gamma = 7;
        vel << 0 ,0 ,0;
        this->mother = parent;

        this->calcForces();
    }        
};
