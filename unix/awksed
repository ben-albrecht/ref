#AWK/SED (General Text Editing Tricks)
#Replace all instances of a particular string in all files, recursively in a directory, with another string
grep -rl matchstring somedir/ | xargs sed -i 's/string1/string2/g'

#Passing variables to awk-one-liners
awk -v "f=$line_number" -v "b=$bar" '(NR==f) { print "foo-", b } 1' FILE
#e.g.
awk -v "n=$banana" -v "s=water" '(NR==n) { print "SMX_SOLVENT", s } 1' template.txt

#Passing variables to awk scripts
<bash command> | ./test.awk variable=<foo>
#e.g.
ls -a | ./test.awk -v"colnumber=5"

#Inserting a line into a text file
awk -v "n=line-number" -v "s=line to insert" '(NR==n) { print s } 1' FILE

#Print line number of a string (foo = string )
awk '/foo/{print NR}' file

#Deleting one line (deletes line 10)
sed '10d' file-name
#OR
awk 'NR == 10 {next} {print}' file
#with input
awk -v “n=$n” 'NR == n {next} {print}' file

#Absolute value in awk (example: avg.awk)
#!/bin/awk -f
function abs(num){
  if (num > 0.0) return num
  else return -num
}
BEGIN{
sum = 0;
}

{
sum += abs($2);
}
END{
print "MUE: ", sum/NR
}

#awk if statement
awk '{ if (x % 2 == 0) print "x is even"; else
        print "x is odd" }'

#variables in sed
sed -i "s/$var1/ZZ/g" "$file"
#if symbols in the sed command (backslash \)
sed -i "s/quote me/\"\\&\"/" "$file"
