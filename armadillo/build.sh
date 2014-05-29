#/bin/bash

if [ -z $1 ]
then
    echo "Give a <file>.cpp as an argument, e.g. \`./build.sh example\`"
else
    g++ $1.cpp -o $1 -O1 -larmadillo
fi

