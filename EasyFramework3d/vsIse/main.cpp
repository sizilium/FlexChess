#include <iostream>
#include "vsIse.h"

using namespace std;

int main()
{
    cout.precision(9);
    
    int arrayx[10] = {1000,0000};
    int arrayy[10] = {0000,0000};
    
    vsIse x(0, 0000, arrayx);
    vsIse y(0, 1100, arrayy);  
    vsIse z;
  
    z+=100;
    
    x.getCout();
    y.getCout();
    z.getCout();
 	
    system("PAUSE");
    return EXIT_SUCCESS;
}
