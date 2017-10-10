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
        void checkCollision();



    Particle(Frame* parent)
    {
        h_0 = 0.0;
        mass = 2.25625;
        rho_0 = 1000.0;
        rho = rho_0;
        press = 1.0;
        ca = 400.0;
        gamma = 7;
        vel << 0 ,0 ,0;
        this->mother = parent;
        h = 0.05*1.5;

        this->calcForces();
    }        
};
