#include <iostream>
#include <exception>

using namespace std;

int main () {
  cout << "Give me a positive integer" << endl;
  int size;
  cin >> size;
  try
  {
    int* myarray= new int[size];
  }
  catch (exception& e)
  {
    cout << "Standard exception: " << e.what() << endl;
  }
  return 0;
}
