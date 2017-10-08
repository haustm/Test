#pragma once
#include <string>
#include <vector>
#include "particle.hpp"

class Frame
{
	public:
	double time;
    double dt;

	std::vector<Particle> particles;
	static Frame initNew();
    void writeFrame();
    void step();
    double kern(double x, double h);
    Vector3d gradKern(Vector3d a, Vector3d b, double h);
    void findNeighbours();
};
