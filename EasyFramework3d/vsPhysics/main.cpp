//#include <iostream>
//#include "vspoint.h"
//#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
	vsPoint point1;
	vsPoint point2;
	
	point1.setCoords(vsIseVector());
	point2.setCoords(vsIseVector(100.0, 0.0, 0.0));
	cout << "Abstand quadrat: " << point.dist_sqr() << endl;
	
	system("PAUSE");
}
