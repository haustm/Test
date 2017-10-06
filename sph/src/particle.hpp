#pragma once

#include <Eigen/Dense>

using namespace Eigen;


class Particle
{
    public:

        Vector3d pos;
        Vector3d f;
        Vector3d vhalf;

        double mass;
        double rho_0, rho, ca, gamma;

        void calcForces();
        void move(double dt);

        void calcP();

    Particle()
    {
        mass = 1000;
        rho_0 = 1000;
        rho = 0;
        ca = 100;
        gamma = 7;
    }        
};
