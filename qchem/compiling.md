# Compiling Q-Chem
Tips and tricks on compiling Q-Chem

## Modules
* [Install and Set up Modules](https://github.com/ben-albrecht/ref/modules.md)

* Download module files from my [git-repo](https://github.com/ben-albrecht/modules)

The remainder of this guide assumes you have modules set up properly.


## Compilers (Choose one)
### Intel Compiler Collection (icc)
* [Download here](https://software.intel.com/en-us/intel-parallel-studio-xe)
* Get the free student version (linux), or a real license ($$)
* Includes MKL Math Library
#### Issues:
* Ubuntu:
	* Fix Ubuntu STD library locations
	* `/usr/include/c++/4.8/bits`
	* `sudo ln -s ../../../x86_64-linux-gnu/c++/4.8/bits/* .`
	* You will have to do this for future versions of C++ STD Library

### GNU Compiler Collection (gcc)
* [Download here](http://sourceforge.net/projects/hpc/files/hpc/gcc/gcc-4.9-bin.tar.gz/download?use_mirror=softlayer-dal&download=) 
* OSX Options:
    * `brew install gcc`
    * [Build instructions for OSX](https://wiki.helsinki.fi/display/HUGG/Installing+the+GNU+compilers+on+Mac+OS+X)
    

## Math Libraries (Choose one)

### MKL
* Part of Intel's [parallel studio compiler suite](https://software.intel.com/en-us/intel-parallel-studio-xe)

### OpenBLAS
* [Download here](https://github.com/xianyi/OpenBLAS)
* OSX: Brew installation will put OpenBlas in `/usr/local/opt/openblas`
* Symbolic link to `$QC_EXT_LIBS/OpenBLAS/..`

#### Issues:
* Compile Errors - undefined references to OpenBLAS functions


### ACML
* [Download here](http://developer.amd.com/tools-and-sdks/cpu-development/amd-core-math-library-acml/acml-downloads-resources/)

1. Run installer shell script, and install in desired location, e.g. /home/ben/opt/acml5.3.1
*  Symbolic link `acml/gfortran64/include/` to `$QC_EXT_LIBS/ACML/include/`
*  Symbolic link `acml/gfortran64/lib/` to `$QC_EXT_LIBS/ACML/lib/`

#### Issues
* gcc:
	* gen_scfman crashes

### ATLAS
* [Download here](http://math-atlas.sourceforge.net/)

## BLAS
* [Download here](http://www.netlib.org/blas/)    
* Easy enough to build from scratch (requires gcc)
* Available on homebrew (OSX) / apt-get (Ubuntu)

## LAPACK
* [Download here](http://www.netlib.org/lapack/)
* * Easy enough to build from scratch (requires BLAS + gcc)


## Optional Libraries

### FFTW
For Fourier Transform Coulomb (FTC) method in Q-Chem
### Boost
For Density Matrix Renormalization Group (DMRG) code in Q-Chem
### BLACS/PBLAS/ScaLAPACK
For vendor math libraries that do not suppy parallel BLAS libraries
### OpenMPI
For distributed MPI parallelization (pick one)
### MPICH2
For distributed MPI parallelization (pick one)


## $QCAUX
    cd $QCAUX
    svn checkout $QCAUXSVN/trunk .
    wget http://www.q-chem.com/download/qc4010/drivers/drivers.small.tar.gz
    tar -xvf drivers.small.tar.gz




## Compiling
1. **Checkout q-chem** 
	* `svn --username=<username> co https://jubilee.q-chem.com/svnroot/qchem/trunk <qchem-directory-name>`
* **Load ze modules**
	* `module load qchem`
* **Build it** (configure or use [qcmake script](https://github.com/ben-albrecht/scripts/qcmake))
	* `./configure help`
		* `./configure ./configure gcc nointracule nomgc noopt2 nolibdftn nonewpath2 debug acml`
		* `cd build`
		* `make`
    * **or** `qcmake -h`
        * `qcmake gcc`
* **Compile and pray** for no errors
* **???**
* `[100%] Built target qcprog.exe` **Profit!!!**



