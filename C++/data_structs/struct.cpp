//  File: struct.cpp
//
//  Programmer: Ben Albrecht
//
//  The goal of this progam is to not only re-familiarize myself with
//  c++ typedef structs, but to also strengthen my understanding by performing
//  "difficult" struct operations.
//
//  To do:
//      √1.0 The Basics
//       2.0 Passing structs to functions
//
//
//
//

// Includes
#include <iostream>

using namespace std;
// function prototypes (so we don't need a header)
void populate_params(int x, void *ptr);
void read_params(void *ptr);

// 1.0 The Basics
// Defining a struct (2 ways):
struct parameters1       // define a structure to hold parameters
{
  double jA1;
  double jB2;
  double jC3;
  int iD4;
};

typedef struct          // define a type to hold parameters
{
  double jA1;
  double jB2;
  double jC3;
  int iD4;
} parameters2;

int main ()
{
  // Note the differences in declaration depending on how the struct is defined
  struct parameters1 params1 ;
  parameters2 params2;

  void *param_ptr; // void pointer to pass our functions

  param_ptr = &params1; // First we will run through programs with parameters1



return 0;
}


void populate_params(int x, void *ptr) {

  //struct parameters *passed_ptr;

  //passed_ptr = (struct parameters *) params_ptr;

  double passed_double_1 = ((struct parameters1 *) ptr)->jA1;
  double passed_double_2 = passed_ptr->b;
  double passed_double_3 = ((struct parameters1 *) ptr)->jC3;
  int passed_int = ((struct parameters *) params_ptr)->num;

  cout << "Passed:   a = " << passed_double_1
    << ", b = " << passed_double_2
    << ", c = " << passed_double_3 << ", num = " << passed_int << endl;

}

void read_params(void *ptr) {

}



