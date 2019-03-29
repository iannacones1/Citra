#!/bin/bash

if [ $# -ne 1 ]
then
    echo "usage:" $0 "TEAM"
    exit 1;
fi

TEAM=$1

DATE=`date +%H%M`

# At 03:00 am try and 
if [ "$DATE" == "0300" ]; then

    echo "Looking for update..."

    cd /home/pi/git/Citra/

    PULL=`git pull`
    ERROR=$?

    if [ $ERROR -ne 0 ]; then
        echo "Error: missing network?"
        exit 1
    fi

    if [ "$PULL" != "Already up-to-date." ]; then
        echo "Building.."
        make clean
	
        make mlbClock
	make Display/Modules/EinkDisplayModule.so
    else
	echo $PULL
    fi

fi

cd /home/pi/git/Citra/bin

./mlbClock --mlbClockComponent::TEAM $TEAM
