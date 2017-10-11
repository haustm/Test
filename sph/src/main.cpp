#include <iostream>
#include "frame.hpp"


using namespace std;

int main()
{
	cout << "SPH - Test Program" << endl;
	
	cout << "Initialize Geometrie... ";
	Frame initFrame = Frame::initNew();
	cout << "done" << endl;

    
    cout << "Write Init Frame... " ;
	initFrame.writeFrame();
	cout << "done" << endl;


    cout << "Start Iteration..." << endl ;
    
    int iteration = 0;
    
    while(iteration < 50000)
    {
        cout << "Start Iteration " << iteration << " ... " << endl;
        initFrame.step();
        if (iteration % 5 == 0) initFrame.writeFrame();
        iteration++;
    }

	
	return 0;
}
