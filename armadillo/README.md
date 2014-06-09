How to compile armadillo
========================
`wget <sourceforge link>`

rename the tar ball, unpack it
`
cd armadillo-*
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=<COMPILE PATH!> ..  
make install
`


Compiling Programs with armadillo
=================================
set up module file, and load module
compile armadillo programs with `-larmadillo`



Adjustments for Q-Chem 
======================
File: $QC/armadillo/include/armadillo_bits/config.hpp.cmake
Comment out the following with `//`, remove build/armadillo, and recompile :
------------------------------
    #define ARMA_BLAS_UNDERSCORE 

File: $QC/build/armadillo/include/armadillo_bits/config_gmake.hpp
    #define ARMA_BLAS_UNDERSCORE 
