#!/bin/bash

xauth list | grep unix`echo $DISPLAY | cut -c10-12` > /tmp/xauth
#sudo su
sudo xauth add `cat /tmp/xauth`

cd /home/pi/git/Citra/bin/

ulimit -c unlimited
ulimit -c

sudo ./mlbClock
