#!/bin/bash

cd ~/git/

mkdir 7.5inch-e-paper-hat-code

cdr 7.5inch-e-paper-hat-code

wget https://www.waveshare.com/w/upload/0/06/7.5inch-e-paper-hat-code.7z

7z x 7.5inch-e-paper-hat-code.7z

cd raspberrypi/bcm2835/

make

sudo ./epd
