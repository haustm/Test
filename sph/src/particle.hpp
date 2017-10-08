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
        void calcRho0();



    Particle(Frame* parent)
    {
        rho_0 = 8.8;
        mass = rho_0 * 0.1*0.1;
        rho = 30.0;
        press = 0.4;
        ca = 0.01;
        gamma = 7;
        vel << 0 ,0 ,0;
        this->mother = parent;

        this->calcForces();
    }        
};
