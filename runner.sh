#!/bin/bash

FINISH=0
trap 'FINISH=1' SIGINT


while [ $FINISH -eq 0 ]
do

echo `date`

./run.bash

done

