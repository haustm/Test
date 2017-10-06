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

	
	return 0;
}
