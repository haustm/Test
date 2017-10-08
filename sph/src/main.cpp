#include <iostream>
#include "frame.hpp"


using namespace std;

int main()
{
	cout << "SPH - Test Program" << endl;
	
	cout << "Initialize Geometrie... ";
	Frame initFrame = Frame::initNew();
	cout << "done" << endl;

    /*
    for(auto p : initFrame.particles)
    {
        if(p.pos[0] < 0.3) p.vel << 0.2,0.3,0.0;
    }

    */

    cout << "Write Init Frame... " ;
	initFrame.writeFrame();
	cout << "done" << endl;


    cout << "Start Iteration..." << endl ;
    
    int iteration = 0;
    while(iteration < 5000)
    {
        cout << "Start Iteration " << iteration << " ... " << endl;
        initFrame.step();
        if (iteration % 10 == 0) initFrame.writeFrame();
        iteration++;
    }

	
	return 0;
}
