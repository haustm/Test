#include "frame.hpp"
#include "particle.hpp"

Frame Frame::initNew()
{
    Frame newF = Frame();
    
    for(int i = 0; i < 100; i++)
    {
		for(int j = 0; j < 100; j++)
		{
			Particle tmp;
			tmp.x = i * 0.1 ;
			tmp.y = j * 0.1 ;
			tmp.z = 0;
			newF.particles.push_back(tmp);
		}
    }

    return newF;    
}
