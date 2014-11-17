# Compiling Q-Chem On Ubuntu #
## Prerequisites: ##
### Modules (TODO)
#### Install Modules
#### Set up Modules
##### Download from git-repo
##### Set up procs.tcl and .bashrc edits
##### Edits to etc/modules or whatever
##### module use, module avail, module load

The remainder of this guide assumes you have modules set up properly.

### $QC_EXT_LIBS
#### Compilers
* Intel Compilers
    * Get the free student version, a real license, or from a friend)
    * Fix Ubuntu STD library locations
    * `/usr/include/c++/4.8/bits`
    * `sudo ln -s ../../../x86_64-linux-gnu/c++/4.8/bits/* .`
    * You will have to do this for future versions of C++ STD Library
* GNU Compilers Compilation (gcc)
    * Install gcc

#### Math-Libraries
##### Confirmed Working (by me)
* ACML
    * Crashes with gen_scfman, when compiled with gcc
    1. Download [ACML Version 5 ](http://developer.amd.com/tools-and-sdks/cpu-development/amd-core-math-library-acml/acml-downloads-resources/)
    *  Run installer shell script, and install in desired location, e.g. /home/ben/opt/acml5.3.1
    *  Create (mkdir) ACML directory in $QC_EXT_LIBS with subdirectories lib/ and include/
    *  Symbolically link (ln -s) path to acml/gfortran64/include/acml.h into ACML/include/
    *  Symbolically link (ln -s) path to acml/gfortran64/lib/libacml.a and libacml_mp.a into ACML/lib/

##### Unconfirmed (by me)
* OpenBLAS
	* Compile Errors - undefined references to OpenBLAS functions
* MKL
	* Eric claims it works
* atlas

#### FFTW - Optional (TODO)



### $QCAUX
	cd $QCAUX
	svn checkout $QCAUXSVN/trunk .
	wget http://www.q-chem.com/download/qc4010/drivers/drivers.small.tar.gz
	tar -xvf drivers.small.tar.gz




## Step-by-Step

1. Checkout q-chem trunk or branch from SVN jubilee server or odysseus git repository

* Load ze modules

* Build it
	* **Use** `qcmake gcc`
		* Get qcmake from my scripts [git-repository](https://github.com/exit-1/scripts/blob/master/qcmake)

	* **or**  `./configure ./configure gcc nointracule nomgc noopt2 nolibdftn nonewpath2 debug acml`, `cd build`, and `make`

* `.....`
 `Building CXX object CMakeFiles/qcprog.exe.dir/main.C.o`
`Linking CXX executable qcprog.exe`
`[100%] Built target qcprog.exe`
`????`


* Profit!!!




