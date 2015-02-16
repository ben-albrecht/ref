# gcc

## Basic
General Format

`gcc <options> <file> <options>`

Compile to a.out

`gcc foo.c`

Compile to named output
`gcc foo.c -o foo.out`

## Switches

Compiling process goes like:

    (C/C++ file) -> preprocess -> compiler proper -> (assembly) ->
    assembler -> (object file) ->
    linker (utilizes many object files) -> (executable binary)

Compile to object.o (do not link)

`gcc -c foo.c`

Compile to assembly.s (do no assemble)

`gcc -E foo.c`

Compile to preprocessed (do not run compiler proper)

`gcc -S foo.c`

## Warnings (-W)

-Wall : Show all warnings

-Wextra : Shows more warning conditions

-Werror : interpret warnings as errors (kills compile)

-w      : Switch that turns off all warnings

# Compile Multiple Files

Consider foo.c and bar.c where foo.c declares and calls a function from bar.c

Create 2 object files

`gcc -c foo.c -o foo.o`

`gcc -c bar.c -o bar.o`

Link the 2 objects into a binary

`gcc foo.o bar.o -o foobar`


## Linking Libraries

### System Libraries

To link a system library, such as libm.so (gcc math library):

`gcc foo.c -o foo -lm

`-lx` will search in library paths for libx.so, libx.a, and libx.o

`ldd foo` will show libraries that binary foo is linked to

### Non-System Libraries

To link a non-system library, such as /home/user/libs/libbar.so,
use `-L` to temporarily append a direct or relative path to search:

`gcc foo.c -o foo -L/home/user/libs -lbar`


## Compile a Shared Library

To compile a shared library:

`gcc foo.c -o libfoo.so -shared`

To link to that shared library:

`gcc bar.c -o bar -L/path/to/libdir -lfoo`

or if in same directory:

`gcc -c bar.c -o bar.o`
`gcc bar.c libfoo.so -o foobar`


To include headers that are in a non-standard directory:

`gcc foo.c -o foo -I/home/user/project/include`

## TODO:

* Static Linking
* Optmization
* Debugging
* More switches

http://phoxis.org/2009/12/01/beginners-guide-to-gcc/
