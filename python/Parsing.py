## General Text Parsing Techniques ##


# Let's try some Q-Chem outputs

qcoutput = open("h2odim.out")
for line in qcoutput :
    fields = line.split()
    if "Convergence" in line :
        print fields[1]

qcoutput.close()
