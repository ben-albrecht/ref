//  File: pointers.cpp
//
//  Programmer: Ben Albrecht
//
//  The goal of this progam is to not only re-familiarize myself with
//  c++ pointers, but to also strengthen my understanding by performing
//  "difficult" pointer operations.
//
//  To do:
//      √1.0 The Basics
//      1.1 Arrays and pointers
//      2.0 Functions and pointers
//      2.1 Passing an integer
//      2.2 Passing an array
//      2.3 Passing a class object
//      3.0 Void Pointers
//
//      later: pointers to pointers (int main (argc argv))
//      void pointers and casting them
//
//
//
//

// Includes
#include <iostream>
#include "pointers.h"

using namespace std;

int main ()
{

    // 1.0 The Basics
    // I like to think of the reference operator (&) as "the address of"
    // and the dereference operator (*) as "the contents of"

    int * a_ptr, * b_ptr;
    int alpha, beta;
    // Below, we use a pointer, test_ptr to set the values of test1 and test2
    // The value of test_ptr = & (the address of) test1
    a_ptr = &alpha;

    // * (The contents of the address value) test_ptr = 10
    // Therefore the contents of the address of test1 = 10
    // Therefore test1 = 10
    *a_ptr = 10;

    // Repeating for test2
    b_ptr = &beta;
    *b_ptr = 20;
    cout << "alpha is " << alpha << endl; //10
    cout << "beta is " << beta << endl; //20

    // 2.0 Functions and Pointers
    cout << "(*+) takes dereferenced integers as inputs" << endl;
    cout << "(&+) takes referenced integers as inputs" << endl;
    //
    cout << "alpha + beta = " << add(alpha, beta) << endl;
    cout << " * a_ptr + * b_ptr = " << add(* a_ptr, * b_ptr) << endl;
    //
    cout << " * a_ptr (&+) * b_ptr = " << add_ref(* a_ptr, * b_ptr) << endl;
    cout << " alpha (&+) beta = " << add_ref(alpha, beta) << endl;
    //
    cout << " a_ptr (*+) b_ptr = " << add_deref(a_ptr, b_ptr) << endl;
    cout << " & alpha (*+) & beta = " << add_deref(& alpha, & beta) << endl;


    // 2.3
    // Declaring Object
    Vehicle Truck(4, 2, 80.0);

return 0;
}

// 2.0 Functions and Pointers
int add(int a, int b) // (+)
{
    return(a+b);
}

int add_deref(int * a, int * b) // (*+)
{

    return(* a + * b);
}

int add_ref(int & a, int & b) // ($+)
{

    return(  a +  b);
}

// 2.3 Class Definitions

int Vehicle::get_passengers() {
    return passengers;
}

void Vehicle::set_passengers(int a) {
    a += 1; //TMP
}

Vehicle::Vehicle(int pssgrs, int whls, double mx_spd) {
    passengers = pssgrs;
    wheels = whls;
    max_speed = mx_spd;
}

