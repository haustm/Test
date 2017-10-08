#include "particle.hpp"
#include "frame.hpp"
#include <iostream>


void Particle::move(double dt)
{
    calcRho();
    calcP();
    //moveRho();

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
    this->press = pa;
}

void Particle::moveRho()
{
    double sum = 0;
    double h = 0.4;

    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        double x = (this->pos - p.pos).norm();
        if ( x > 2*h || x < 1e-12) continue;
        sum += p.mass *(this->vel - p.vel).dot(
            (-2.0*x*exp(-1.0*x*x/(h*h)) / (h*h*h*h*sqrt(3.14159))) * (this->pos - p.pos)
            );
    }

    this->rho += sum * mother->dt;
}

void Particle::calcRho()
{
    double sum = 0;
    double h = 0.4;
    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        double x = (this->pos - p.pos).norm() / h;
        if ( x > 2*h || x < 1e-12) continue;
        sum += p.mass * (exp(-1.0*x*x/(h*h)) / (h*h*sqrt(3.14159)));
    }
    this->rho = sum;
}

void Particle::calcForces()
{
    this->f *= 0;
    Vector3d g(0,-9.81*0,0);
    
    this->f += this->mass * g;

    double sum = 0;
    double h = 0.4;
    Vector3d grad;
    grad << 0,0,0 ;
    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        double x = (this->pos - p.pos).norm();
        if ( x > 2*h || x < 1e-12) continue;
        double masse = p.mass;
        double Pa = this->press;
        double Pb = p.press;
        sum = p.mass * (Pa / (this->rho * this->rho) + Pb / (p.rho*p.rho)) ;
        double deriv = (-2.0*x*exp(-1.0*x*x/(h*h)) / (h*h*h*h*sqrt(3.14159))) ;
        grad = deriv * (this->pos - p.pos) / x;
        grad *= sum ;
    }
    grad *= -1;
    this->f += grad;
    //std::cout << f[0] << " " << f[1] << std::endl;
}

