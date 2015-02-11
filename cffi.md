# cffi

## FFI

### cdef()
"Parse the given C source.  This registers all declared functions,
types, and global variables.  The functions and global variables can
then be accessed via either 'ffi.dlopen()' or 'ffi.verify()'.
The types can be used in 'ffi.new()' and other functions.
If 'packed' is specified as True, all structs declared inside this
cdef are packed, i.e. laid out without any field alignment at all."

cdef basically reads C source code written inline and and registers
the type and signature of the functions, types, and variables.

### dlopen()
"Load and return a dynamic library identified by 'name'.
The standard C library can be loaded by passing None.
Note that functions and types declared by 'ffi.cdef()' are not
linked to a particular library, just like C headers; in the
library we only look for the actual (untyped) symbols."

dlopen loads a namespace of a library.
dlopen(None) will load the global namespace (standard C library)


### verify()
"Verify that the current ffi signatures compile on this
machine, and return a dynamic library object.  The dynamic
library can be used to call functions and access global
variables declared in this 'ffi'.  The library is compiled
by the C compiler: it gives you C-level API compatibility
(including calling macros).  This is unlike 'ffi.dlopen()',
which requires binary compatibility in the signatures."

verify is an alternative to dlopen. Instead of loading a library,
it generates and compiles the given C code, verifying that the declarations
are successful. C compiler errors would be returned here.

### new()
"Allocate an instance according to the specified C type and
return a pointer to it.  The specified C type must be either a
pointer or an array: ``new('X *')`` allocates an X and returns
a pointer to it, whereas ``new('X[n]')`` allocates an array of
n X'es and returns an array referencing it (which works
mostly like a pointer, like in C).  You can also use
``new('X[]', n)`` to allocate an array of a non-constant
length n.

The memory is initialized following the rules of declaring a
global variable in C: by default it is zero-initialized, but
an explicit initializer can be given which can be used to
fill all or part of the memory.

When the returned <cdata> object goes out of scope, the memory
is freed.  In other words the returned <cdata> object has
ownership of the value of type 'cdecl' that it points to.  This
means that the raw data can be used as long as this object is
kept alive, but must not be used for a longer time.  Be careful
about that when copying the pointer to the memory somewhere
else, e.g. into another structure."

Allocates C objects, filling them with zeros
unless a second optional arg is given (initializer)
