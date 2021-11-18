#!/bin/bash
echo
echo "> Compile source code."
make
echo

echo "> Calculate."
#cal_t=$((time bin/serial.out -problemType $2 -N $4 > out/serial.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
#echo -e "With serial \t\t $cal_t"

cal_t=$((time bin/parallel.out -problemType $2 -N $4 > out/parallel.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
echo -e "With parallel \t\t $cal_t"

if [ "$2" = "all" ]; then
  cal_t=$((time bin/parallel_all.out $4 > out/parallel_all.txt) 2>&1 > /dev/null | grep real | awk '{print $2}')
  echo -e "With parallel (v2.0) \t $cal_t"
else
  echo "No implementation of parallel_find.cpp were found."
  dot -Tpng graph.dot -o img/graph.png
fi
