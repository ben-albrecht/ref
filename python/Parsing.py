## General Text Parsing Techniques ##


# Let's try some Q-Chem outputs

energies=["Full PBE: ", "PBE-in-CCSD(T): ", "Full CCSD(T): "]
qcoutput = open("h2odim.out")
for line in qcoutput :
    fields = line.split()
    if "Convergence" in line :
        print fields[1]
        

qcoutput.close()
