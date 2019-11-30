#!/bin/bash

mkdir shell_tut
cd shell_tut

for((i=0; i<10; i++)); do
   touch test_$i.dat
done
