#!/bin/sh 
#Join root files of GoF test corresponding to mass points with 1 GeV step:
for i in 3.6 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
do

  echo "  "
  echo "  "
  
  eval "mass=${i}p0"

  if (( $(echo "${i} < 4" |bc -l) )); then
  eval "mass=3p6"
  fi

eval "file=higgsCombineTest.GoodnessOfFit.mH$i.123456"

./hadd.sh GOF_ma$mass $file

done
