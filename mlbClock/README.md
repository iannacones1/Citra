# MLB Clock

![](Preview.png "Screen Example")

## Raspberry Pi Raspbian Install/Setup Guide

[Download Raspbian Stretch Lite](https://downloads.raspberrypi.org/raspbian_lite_latest)

[Installing operating system](https://www.raspberrypi.org/documentation/installation/installing-images/README.md)

## Update Raspbian
    sudo apt-get update

## Configure Raspbian
    sudo raspi-config

Things to update

 * Setup WiFi `2 Network Options` > `N2 Wi-fi`
 * Set Local Time `4 Localisation Options` > `I2 Cange Timezone` 
 * enable i2c `5 Interface Options` > `P5 I2C`
 * enable ssh (optional)

## install git
    sudo apt-get install git

## Clone Citra
    cd /home/pi/
    mkdir git
    cd git
    git clone https://github.com/iannacones1/Citra.git

## Install boost
    sudo apt-get install libboost-all-dev

## Install cairo
    sudo apt-get install libcairo2-dev

## install cairomm
    sudo apt-get install cairomm-1.0-dev

## Install lbcm2835
    wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.55.tar.gz
    tar zxvf bcm2835-1.55.tar.gz
    cd bcm2835-1.55/
    ./configure
    make
    sudo make check
    sudo make install

## Install rapidXml
    wget https://downloads.sourceforge.net/project/rapidxml/rapidxml/rapidxml%201.13/rapidxml-1.13.zip
    unzip rapidxml-1.13.zip
    sudo cp -r rapidxml-1.13 /usr/include/
    sudo sh -c "echo '#include \"rapidxml-1.13/rapidxml.hpp\"' > /usr/include/rapidxml"

## Install boost beast (and supporting boost header only libs)
    cd ~/git; \
    for lib in beast mp11 asio core config type_traits container_hash utility optional; \
    do \
        echo $lib; \
        git clone https://github.com/boostorg/$lib.git; \
        cd $lib; \
        sudo cp -r include/boost/* /usr/include/boost/; \
        cd ../; \
        rm -rf $lib; \ 
    done

## install Qt (optional)
    sudo apt-get install qt4-dev-tools

## install jsoncpp (optional)
    sudo apt-get install libjsoncpp-dev

## Build mlbClock
    cd /home/pi/git/Citra/
    make mlbClock
    make Display/Modules/EinkDisplayModule.so

## Add job to /etc/crontab
If you felt so inclined you could replace `PHI` with the team of your choice. But why would you do that? go Phils!

    sudo sh -c "echo \"*   *    * * *   pi      /home/pi/git/Citra/mlbClock/scripts/cronjob PHI\" >> /etc/crontab"


