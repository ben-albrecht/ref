==== Valgrind With Q-Chem ====
1. Compile Q-Chem with DEBUG

$QC/bin/qchem_for_debug foo.in
valgrind $QC/exe/qcprog.exe ./foo.in ./foo_scratch


== Common Flags ==

logfile: --log-file=out.log
turn off error limit: --error-limit=no
    allows number of errors to exceed 1million (happens in q-chem sometimes)


== Profiling ==
valgrind --tool=callgrind ./(Your binary)


== KCacheGrind Compatibility ==
valgrind --tool=callgrind -v --dump-every-bb=10000000 <executable>
