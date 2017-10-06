#include "particle.hpp"
#include <iostream>

void Particle::calcForces()
{
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
