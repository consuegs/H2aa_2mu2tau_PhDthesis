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

combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2018_ma$mass.txt --algo=AD --fixedSignalStrength=0.0 -m $massf

# To run locally MC Toys with r fixed and not fixed, as well as Observed with r not fixed
#echo "MC Toys, r fixed"
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2018_ma$mass.txt --algo=AD --fixedSignalStrength=0.0 -m $massf -t 100 -s 123456

#echo "MC Toys"
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2018_ma$mass.txt --algo=AD -m $massf -t 100 -s 123456

#echo "Observed"
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2018_ma$mass.txt --algo=AD -m $massf

done

