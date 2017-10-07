#include "particle.hpp"
#include <iostream>

void Particle::calcForces()
{
    calcRho();

    this->f *= 0;
    Vector3d g(0,0,-9.81);
    
    this->f += this->mass * g;
}


void Particle::move(double dt)
{
    /* Euler
    Vector3d accel = this->f / this->mass;
    this->pos += this->vel * dt;
    this->vel += accel * dt;
    calcForces();
    */

    /* Leapfrog
    */
    Vector3d accel = this->f / this->mass;
    this->vel += accel * dt * 0.5;
    this->pos += this->vel * dt;
    calcForces();
    accel = this->f / this->mass;
    this->vel += 0.5 * accel * dt;
}


void Particle::calcP()
{
    double pa = rho_0 * ca*ca / gamma * ( pow((rho / rho_0), gamma) - 1 );
}

void Particle::calcRho()
{
    double sum = 0;
    double h = 0.1;
    for(auto p : neighbours)
    {
        double x = (this->pos - p->pos).norm();
        double vel = (this->vel - p->vel).norm();
        sum = p->mass * vel * (-2.0*x*exp(-1.0*x*x/(h*h)) / (h*h*h*sqrt(3.14159)));
    }
    this->rho += sum * 0.1;
}
