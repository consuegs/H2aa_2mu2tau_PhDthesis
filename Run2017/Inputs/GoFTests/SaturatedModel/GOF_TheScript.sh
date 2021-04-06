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

#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma$mass.txt --algo=saturated --fixedSignalStrength=0.0 -m $massf
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma${mass}_lep_lep.txt --algo=saturated --fixedSignalStrength=0.0 -m $massf
#mv higgsCombineTest.GoodnessOfFit.mH${massf}.root higgsCombineTest.GoodnessOfFit.mH${massf}_lep_lep.root
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma${mass}_lep_had.txt --algo=saturated --fixedSignalStrength=0.0 -m $massf
#mv higgsCombineTest.GoodnessOfFit.mH${massf}.root higgsCombineTest.GoodnessOfFit.mH${massf}_lep_had.root
combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma${mass}_had_had.txt --algo=saturated --fixedSignalStrength=0.0 -m $massf
mv higgsCombineTest.GoodnessOfFit.mH${massf}.root higgsCombineTest.GoodnessOfFit.mH${massf}_had_had.root

# To run locally MC Toys with r fixed and not fixed, as well as Observed with r not fixed
#echo "MC Toys, r fixed"
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma$mass.txt --algo=saturated --fixedSignalStrength=0.0 -m $massf -t 100 -s 123456

#echo "MC Toys"
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma$mass.txt --algo=saturated -m $massf -t 100 -s 123456

#echo "Observed"
#combine -M GoodnessOfFit ../../DataCards/haa-13TeV_2017_ma$mass.txt --algo=saturated -m $massf

done

