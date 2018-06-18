#!/bin/bash
g++ -std=c++11 compute.cpp -o compute
cd ..
rm -rf WordMask
mkdir WordMask
cd WordMask
touch text.cpp
git init
git add .
git commit -m "init"
# echo $(date) >> text.cpp
# git commit -m "modify text: $(date)" --date="Wed Feb 16 14:00 2011 +0100"

for timestamp in $( ../mask/compute $@ )
do
	updated=$( echo $timestamp | tr "#" " " )
    # echo $updated
    echo $updated >> text.cpp
    git add .
    git commit -m "add timestamp in file: $updated" --date="$updated" --quiet
done