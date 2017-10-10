#pragma once
#include <string>
#include <vector>
#include "particle.hpp"

class Frame
{
	public:
	double time;
        double dt;
        int N;

	std::vector<Particle> particles;
	static Frame initNew();
        void writeFrame();
        void step();
    
        double kern(double x, double h);
        Vector3d gradKern(Vector3d a, Vector3d b, double h);
    
        double kern2(double x, double h);
        Vector3d gradKern2(Vector3d a, Vector3d b, double h);
    
        double kern3(double x, double h);
        Vector3d gradKern3(Vector3d a, Vector3d b, double h);
        
        void findNeighbours();
};
