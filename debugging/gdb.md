(gdb)
--- Q-Chem ---
1. Compile With Debug (-g)

gdb $QC/exe/qcprog.exe
run foo.in foo_scratch


Print Arrays

Print 1st element:
  print (int []) *foo 

Print 3 elements: (all the same)
  print (int [3]) *foo
  p *foo@3
  p foo[0]@3

Print memory addresses
  p foo@3
