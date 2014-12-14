#include "stdio.h"
#include <iostream>
using namespace std;


int main ()
{

    int val = 5;
    int y = 0;
    int z = y++;
    cout << "z = y++ = " << z << endl;
    cout << "y = " << y << endl;
    y = 0;
    z = ++y;
    cout << "z = ++y = " << z << endl;
    cout << "y = " << y << endl;
    
    cout << "x++" << endl;
    for (int x = 0; x < val; x++) {
        cout << x << endl;
    }

    cout << "++x" << endl;
    for (int x = 0; x < val; ++x) {
        cout << x << endl;
    }
}    
