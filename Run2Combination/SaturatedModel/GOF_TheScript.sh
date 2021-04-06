#!/bin/sh
# $1 - number of jobs

mass=mass
massf=massf

for i in 3.6 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21
do

  echo "  "
  echo "  "
  
  eval "mass=${i}p0"

  if (( $(echo "${i} < 4" |bc -l) )); then
  eval "mass=3p6"
  fi

  eval "massf=${i}"

echo "Observed, r fixed"
echo "  "
echo "Running GoF test for mass point Ma = $massf GeV"
echo "  "

combine -M GoodnessOfFit ../haa-13TeV_Run2_ma$mass.txt --algo=saturated --fixedSignalStrength=0.0 -m $massf

done

