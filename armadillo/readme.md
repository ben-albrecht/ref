How to compile armadillo
=======================

wget <sourceforge link>
rename the tar ball, unpack it
cd armadillo-*
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<COMPILE PATH!> ..  
make install

set up module file, and load module
compile armadillo programs with -larmadillo

