#include "particle.hpp"
#include "frame.hpp"
#include <iostream>


void Particle::move(double dt)
{
    calcRho();
    calcP();
    moveRho();

    // Euler
    Vector3d accel = this->f / this->mass;
    this->pos += this->vel * dt;
    this->vel += accel * dt;
    calcForces();
    

    /* Leapfrog

    Vector3d accel = this->f / this->mass;
    this->vel += accel * dt * 0.5;
    this->pos += this->vel * dt;
    calcForces();
    accel = this->f / this->mass;
    this->vel += 0.5 * accel * dt;
    */
}


void Particle::calcP()
{
    //std::cout << this->rho << " ";
    //std::cout << this->press << " ";
    double pa = rho_0 * ca*ca / gamma * ( pow((rho / rho_0), gamma) - 1 );
    this->press = pa;
    //std::cout << pa << " ";
}

void Particle::moveRho()
{
    double sum = 0;
    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        sum += p.mass * (this->vel - p.vel).dot( mother->gradKern2(this->pos, p.pos, h)) ;
    }

    this->rho += sum * mother->dt;
}

void Particle::calcRho()
{
    double sum = 0;
    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        double x = (this->pos - p.pos).norm() / h;
        //if ( x > 2*h || x < 1e-12) continue;
        sum += p.mass * this->mother->kern2(x, h);
    }
    this->rho = sum;
    //double hnew = 1.3 * pow(( this->mass / this->rho), 0.5) ;
    //if (hnew > 0 and hnew < 10) this->h = hnew;
    //std::cout <<sum << " "<< "" << " ";
    //this->h = h_0 * sqrt(rho_0 / rho );
}
void Particle::calcRho0()
{
    double sum = 0;
    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        double x = (this->pos - p.pos).norm() / h;
        sum += p.mass * this->mother->kern2(x, h);
    }
    std::cout << sum << std::endl;
    this->rho_0 = sum;
}


double Particle::calcDamp(Particle& p)
{
    double alpha = 0.3;
    double meanRho = 0.5 * (this->rho + p.rho);
    Vector3d vab = this->vel - p.vel;
    Vector3d rab = this->pos - p.pos;
    double d = - alpha * this->ca / meanRho * vab.dot(rab) / rab.norm();
    //std::cout << d << " ";
    return d;
}


void Particle::calcForces()
{
    this->f *= 0;
    Vector3d g(0,-9.81*0,0);
    
    this->f += this->mass * g;

    Vector3d grad;
    grad << 0,0,0 ;
    for(auto& p : this->mother->particles)
    {
        if (p.id == this->id) continue;
        double x = (this->pos - p.pos).norm();
        //if ( x > 2*h || x < 1e-12) continue;
        double Pa = this->press;
        double Pb = p.press;
        double damping = calcDamp(p);
      
        grad += p.mass * (Pa / (this->rho * this->rho) + Pb / (p.rho*p.rho) + damping) * mother->gradKern2(this->pos, p.pos,h) ;
    }
    grad *= -1;
    this->f += grad;
}

