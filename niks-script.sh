#!/bin/bash
printf "Threads, Time\n" > results.csv
for threads in 1 2 3 4 5 6 7 8
do
    printf $threads
    printf ","
    mpirun -np $threads ./poker
    printf "\n"
done >>results.csv
