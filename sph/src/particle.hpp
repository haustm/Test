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
        double h, h_0;

        void move(double dt);

        void calcForces();
        void calcP();
        void moveRho();
        void calcRho();
        void calcRho0();
        double calcDamp(Particle& p);



    Particle(Frame* parent)
    {
        h_0 = 0.7;
        mass = 0.25*4;
        rho_0 = 100 * mass / 1.0 / 3;
        rho = rho_0;
        press = 1.0;
        ca = 1.0;
        gamma = 7;
        vel << 0 ,0 ,0;
        this->mother = parent;
        h = 1.0;

        this->calcForces();
    }        
};
