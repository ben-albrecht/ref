#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;


int main()
  {
    // constructors
    mat A(2,2); // must be symmetric and postive-definite (real positive eigenvalues, Hermitian matrices are positiv defnite)
    mat B(2,2);
    mat C(2,2); // constructors

    A.zeros();
    B.ones();
    C.zeros();

    // Form Hermitian Matrix
    A(0,0) = 1;
    A(1,1) = 1;
    B(0,1) = 0;

    C = chol(A);

    cout << A << endl;
    cout << B << endl;
    cout << "chol(A)" << endl;
    cout << C << endl;

    C = chol(B);

    cout << "chol(B)" << endl;
    cout << C << endl;
    return 0;
  }

