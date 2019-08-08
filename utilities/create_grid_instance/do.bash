#!/usr/bin/env bash

for n in 5 10 ;
do
  for m in 5 10;
  do
    counter=1
    for c in 0.05 0.15 0.25 0.35;
    do
      "./GRID" --n $n --m $m --p $counter --c $c;
      let counter=counter+1;
    done
  done
done


