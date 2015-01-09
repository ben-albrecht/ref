EXECUTION COMMANDS

Launch a process no arguments.
(lldb) run
(lldb) r

Launch a process with arguments <args>.
(lldb) r <args>

Launch a process for with arguments a.out 1 2 3 without having to supply the args every time.
% lldb -- a.out 1 2 3
(lldb) run
...
(lldb) run

(lldb) settings set target.run-args 1 2 3
(lldb) run
...
(lldb) run

Launch a process with arguments in new terminal window (Mac OS X only).
(lldb) process launch --tty -- <args>
(lldb) pro la -t -- <args>

Launch a process with arguments in existing terminal /dev/ttys006 (Mac OS X only).
(lldb) process launch --tty=/dev/ttys006 -- <args>
(lldb) pro la -t/dev/ttys006 -- <args>

Set environment variables for process before launching.
(lldb) settings set target.env-vars DEBUG=1
(lldb) set se target.env-vars DEBUG=1
(lldb) env DEBUG=1

Unset environment variables for process before launching.
(lldb) settings remove target.env-vars DEBUG
(lldb) set rem target.env-vars DEBUG

Show the arguments that will be or were passed to the program when run.
(lldb) settings show target.run-args
target.run-args (array of strings) =
[0]: "1"
[1]: "2"
[2]: "3"

Set environment variables for process and launch process in one command.
(lldb) process launch -v DEBUG=1

Attach to a process with process ID 123.
(lldb) attach -p 123

Attach to a process named "a.out".
(lldb) pro at -n a.out

Wait for a process named "a.out" to launch and attach.
(lldb) pro at -n a.out -w

Attach to a Darwin kernel in kdp mode on system "eorgadd".
Do a source level single step in the currently selected thread.
(lldb) step
(lldb) s

Do a source level single step over in the currently selected thread.
(lldb) next
(lldb) n

Do an instruction level single step in the currently selected thread.
(lldb) si

Do an instruction level single step over in the currently selected thread.
(lldb) ni

Step out of the currently selected frame.
(lldb) thread step-out
(lldb) finish

Return immediately from the currently selected frame, with an optional return value.
(lldb) thread return <RETURN EXPRESSION>

Backtrace and disassemble every time you stop.
(lldb) target stop-hook add
Enter your stop hook command(s). Type 'DONE' to end.
> bt
> disassemble --pc
> DONE
Stop hook #1 added.


BREAKPOINT COMMANDS


Set a breakpoint at all functions named main.
(lldb) br s -n main
(lldb) b main

Set a breakpoint in file test.c at line 12.
(lldb) br s -f test.c -l 12
(lldb) b test.c:12

Set a breakpoint at all C++ methods whose basename is main.
(lldb) breakpoint set --method main
(lldb) br s -M main

Set a breakpoint at and object C function: -[NSString stringWithFormat:].
(lldb) breakpoint set --name "-[NSString stringWithFormat:]"
(lldb) b -[NSString stringWithFormat:]

Set a breakpoint at all Objective C methods whose selector is count.
(lldb) breakpoint set --selector count
(lldb) br s -S count

Set a breakpoint by regular expression on function name.
(lldb) breakpoint set --func-regex regular-expression
(lldb) br s -r regular-expression

Ensure that breakpoints by file and line work for #included .c/.cpp/.m files.
(lldb) settings set target.inline-breakpoint-strategy always
(lldb) br s -f foo.c -l 12

Set a breakpoint by regular expression on source file contents.
(lldb) breakpoint set --source-pattern regular-expression --file SourceFile
(lldb) br s -p regular-expression -f file

Set a conditional breakpoint
(lldb) breakpoint set --name foo --condition '(int)strcmp(y,"hello") == 0'
(lldb) br s -n foo -c '(int)strcmp(y,"hello") == 0'

List all breakpoints.
(lldb) breakpoint list
(lldb) br l

Delete a breakpoint.
(lldb) breakpoint delete 1
(lldb) br del 1


WATCHPOINT COMMANDS


Set a watchpoint on a variable when it is written to.
(lldb) wa s v global_var

Set a watchpoint on a memory location when it is written into.
The size of the region to watch for defaults to the pointer size if no '-x byte_size' is specified.
This command takes raw input, evaluated as an expression returning an unsigned integer pointing
    to the start of the region, after the '--' option terminator.
(lldb) wa s e -- my_ptr

Set a condition on a watchpoint.
(lldb) watch set var global
(lldb) watchpoint modify -c '(global==5)'
(lldb) c
...
(lldb) bt
* thread #1: tid = 0x1c03, 0x0000000100000ef5 a.out`modify + 21 at main.cpp:16, stop reason = watchpoint 1
frame #0: 0x0000000100000ef5 a.out`modify + 21 at main.cpp:16
frame #1: 0x0000000100000eac a.out`main + 108 at main.cpp:25
frame #2: 0x00007fff8ac9c7e1 libdyld.dylib`start + 1

(lldb) frame var global
(int32_t) global = 5

List all watchpoints.
(lldb) watchpoint list
(lldb) watch l

Delete a watchpoint.
(lldb) watchpoint delete 1
(lldb) watch del 1


EXAMINING VARIABLES


Show the arguments and local variables for the current frame.
(lldb) frame variable
(lldb) fr v

Show the local variables for the current frame.
(lldb) frame variable --no-args
(lldb) fr v -a

Show the contents of local variable "bar".
(lldb) frame variable bar 
(lldb) fr v bar 
(lldb) p bar 

Show the contents of local variable "bar" formatted as hex.
(lldb) frame variable --format x bar 
(lldb) fr v -f x bar 

Show the contents of global variable "baz".
(lldb) target variable baz 
(lldb) ta v baz 

Show the global/static variables defined in the current source file.
n/a
(lldb) target variable 
(lldb) ta v 

Display the variables "argc" and "argv" every time you stop.
(lldb) target stop-hook add --one-liner "frame variable argc argv"
(lldb) ta st a -o "fr v argc argv"
(lldb) display argc
(lldb) display argv

Display the variables "argc" and "argv" only when you stop in the function named main.
(lldb) target stop-hook add --name main --one-liner "frame variable argc argv"
(lldb) ta st a -n main -o "fr v argc argv"

Display the variable "*this" only when you stop in c class named MyClass.
(lldb) target stop-hook add --classname MyClass --one-liner "frame variable *this"
(lldb) ta st a -c MyClass -o "fr v *this"
EVALUATING EXPRESSIONS

Evaluating a generalized expression in the current frame.
or if you don't want to see void returns: 
(lldb) expr (int) printf ("Print nine: %d.", 4 + 5)

or using the print alias:
(lldb) print (int) printf ("Print nine: %d.", 4 + 5)

Creating and assigning a value to a convenience variable.
or using the print command 
or using the call command 
In lldb you evaluate a variable declaration expression as you would write it in C:
(lldb) expr unsigned int $foo = 5

Printing the ObjC "description" of an object.
(lldb) expr -o -- [SomeClass returnAnObject]

or using the po alias:
(lldb) po [SomeClass returnAnObject]

Print the dynamic type of the result of an expression.
only works for C++ objects.
(lldb) expr -d 1 -- [SomeClass returnAnObject]
(lldb) expr -d 1 -- someCPPObjectPtrOrReference

or set dynamic type printing to be the default: (lldb) settings set target.prefer-dynamic run-target
Calling a function so you can stop at a breakpoint in the function.
(lldb) expr -i 0 -- function_with_a_breakpoint()

Calling a function that crashes, and stopping when the function crashes.
(lldb) expr -u 0 -- function_which_crashes()


EXAMINING THREAD STATE


Show the stack backtrace for the current thread.
(lldb) thread backtrace
(lldb) bt

Show the stack backtraces for all threads.
(lldb) bt all

Backtrace the first five frames of the current thread.
(lldb) bt 5 (lldb-169 and later)
(lldb) bt -c 5 (lldb-168 and earlier)

Select a different stack frame by index for the current thread.
(lldb) fr s 12
(lldb) f 12

List information about the currently selected frame in the current thread.
(lldb) frame info

Select the stack frame that called the current stack frame.
(lldb) frame select --relative=1

Select the stack frame that is called by the current stack frame.
(lldb) frame select --relative=-1
(lldb) fr s -r-1

Select a different stack frame using a relative offset.
(lldb) frame select --relative 2
(lldb) fr s -r2
(lldb) frame select --relative -3
(lldb) fr s -r-3

Show the general purpose registers for the current thread.
(lldb) register read

Write a new decimal value '123' to the current thread register 'rax'.
(lldb) register write rax 123

Skip 8 bytes ahead of the current program counter (instruction pointer). Note that we use backticks to evaluate an expression and insert the scalar result in LLDB.
(lldb) register write pc `$pc+8`

Show the general purpose registers for the current thread formatted as signed decimal. LLDB tries to use the same format characters as printf(3) when possible. Type "help format" to see the full list of format specifiers.
(lldb) register read --format i
(lldb) re r -f i
(lldb) register read/d

Show all registers in all register sets for the current thread.
(lldb) register read --all
(lldb) re r -a

Show the values for the registers named "rax", "rsp" and "rbp" in the current thread.
(lldb) register read rax rsp rbp

Show the values for the register named "rax" in the current thread formatted as binary.
(lldb) register read --format binary rax
(lldb) re r -f b rax
(lldb) register read/t rax
(lldb) p/t $rax

Read memory from address 0xbffff3c0 and show 4 hex uint32_t values.
(lldb) memory read --size 4 --format x --count 4 0xbffff3c0
(lldb) me r -s4 -fx -c4 0xbffff3c0
(lldb) x -s4 -fx -c4 0xbffff3c0
(lldb) memory read/4xw 0xbffff3c0
(lldb) x/4xw 0xbffff3c0

Read memory starting at the expression "argv[0]".
(lldb) memory read `argv[0]`

NOTE: any command can inline a scalar expression result (as long as the target is stopped) using backticks around any expression:
(lldb) memory read --size `sizeof(int)` `argv[0]`

Read 512 bytes of memory from address 0xbffff3c0 and save results to a local file as text.
(lldb) memory read --outfile /tmp/mem.txt --count 512 0xbffff3c0
(lldb) me r -o/tmp/mem.txt -c512 0xbffff3c0
(lldb) x/512bx -o/tmp/mem.txt 0xbffff3c0

Save binary memory data starting at 0x1000 and ending at 0x2000 to a file.
(lldb) me r -o /tmp/mem.bin -b 0x1000 0x2000

Get information about a specific heap allocation (available on Mac OS X only).
(lldb) process launch --environment MallocStackLogging=1 -- [ARGS]
(lldb) malloc_info --stack-history 0x10010d680

Get information about a specific heap allocation and cast the result to any dynamic type that can be deduced (available on Mac OS X only)
(lldb) command script import lldb.macosx.heap
(lldb) malloc_info --type 0x10010d680

Find all heap blocks that contain a pointer specified by an expression EXPR (available on Mac OS X only).
(lldb) command script import lldb.macosx.heap
(lldb) ptr_refs EXPR 

Find all heap blocks that contain a C string anywhere in the block (available on Mac OS X only).
(lldb) command script import lldb.macosx.heap
(lldb) cstr_refs CSTRING

Disassemble the current function for the current frame.
(lldb) di -f

Disassemble any functions named main.
(lldb) di -n main

Disassemble an address range.
(lldb) di -s 0x1eb8 -e 0x1ec3

Disassemble 20 instructions from a given address.
(lldb) di -s 0x1eb8 -c 20

Show mixed source and disassembly for the current function for the current frame.
n/a (lldb) disassemble --frame --mixed
(lldb) di -f -m

Disassemble the current function for the current frame and show the opcode bytes.
n/a (lldb) disassemble --frame --bytes
(lldb) di -f -b

Disassemble the current source line for the current frame.
n/a (lldb) disassemble --line
(lldb) di -l


EXECUTABLE AND SHARED LIBRARY QUERY COMMANDS

List the main executable and all dependent shared libraries.
(lldb) image list

Look up information for a raw address in the executable or any shared libraries.
(lldb) image lookup --address 0x1ec4
(lldb) im loo -a 0x1ec4

Look up functions matching a regular expression in a binary.
This one finds debug symbols:
(lldb) image lookup -r -n <FUNC_REGEX>

This one finds non-debug symbols:
(lldb) image lookup -r -s <FUNC_REGEX>

Provide a list of binaries as arguments to limit the search.
Find full source line information.
(lldb) image lookup -v --address 0x1ec4

and look for the LineEntry line, which will have the full source path and line range information.
Look up information for an address in a.out only.
(lldb) image lookup --address 0x1ec4 a.out
(lldb) im loo -a 0x1ec4 a.out

Look up information for for a type Point by name.
(lldb) image lookup --type Point
(lldb) im loo -t Point

Dump all sections from the main executable and any shared libraries.
(lldb) image dump sections

Dump all sections in the a.out module.
(lldb) image dump sections a.out

Dump all symbols from the main executable and any shared libraries.
(lldb) image dump symtab

Dump all symbols in a.out and liba.so.
(lldb) image dump symtab a.out liba.so


MISCELLANEOUS

Echo text to the screen.
(lldb) script print "Here is some text"

Remap source file pathnames for the debug session. If your source files are no longer located in the same location as when the program was built --- maybe the program was built on a different computer --- you need to tell the debugger how to find the sources at their local file path instead of the build system's file path.
(lldb) settings set target.source-map /buildbot/path /my/path

