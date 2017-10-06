#include "particle.hpp"
#include <iostream>

void Particle::calcForces()
{
    this->f *= 0;
    Vector3d g(0,0,-9.81);
    
    this->f += g;
}


void Particle::move(double dt)
{
    this->mass = 1000;
    Vector3d accel = this->f / this->mass;

    this->vhalf = this->vhalf + accel * dt;
    this->pos = this->pos + this->vhalf * dt;

}


void Particle::calcP()
{
    double pa = rho_0 * ca*ca / gamma * ( pow((rho / rho_0), gamma) - 1 );
}
