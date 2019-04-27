# Citra

Welcome to my personal C++ common codebase. Used for hobby projects and experimenting.

## Raspberry Pi Raspbian Links

Most of my projects utilize Raspberry Pi and Raspbian

 * [Raspbian Stretch with desktop and recommended software](https://downloads.raspberrypi.org/raspbian_full_latest)
 * [Raspbian Stretch with desktop](https://downloads.raspberrypi.org/raspbian_latest)
 * [Raspbian Stretch Lite](https://downloads.raspberrypi.org/raspbian_lite_latest)

[Installing operating system](https://www.raspberrypi.org/documentation/installation/installing-images/README.md)

### Setup Raspbian headless

To setup wifi headless make a file `/boot/wpa_supplicant.conf` on the SD card. Content as follows:

    ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
    update_config=1
    country=US

    network={
            ssid="«your_SSID»"
            psk="«your_PSK»"
    }

If you don't wish to store your wifi password in plain text, use `wpa_passphrase` to generate the hash


To setup SSH headless make a file `/boot/ssh` on the SD card. Content of the file doesn't matter.


## Hardware Links

Some of the hardware this library supports

 * [Raspberry Pi 16x2 LCD+Keypad](https://www.adafruit.com/product/1115)
 * [Power Switch Tail](https://www.powerswitchtail.com/)
 * [7.5" E-Ink Display](https://www.waveshare.com/7.5inch-e-Paper-HAT.htm)
 * [Digital Temperature Sensor](https://www.adafruit.com/product/381)
