#pragma once
#include <vector>
#include "particle.hpp"

class Frame
{
	public:
	double time;
	std::vector<Particle> particles;
	static Frame initNew();
    void writeFrame();
};
