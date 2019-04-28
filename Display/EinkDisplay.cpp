#include <bcm2835.h>

#include "EinkDisplay.h"

namespace Citra { namespace Display {

static const int RST_PIN  = 17;
static const int DC_PIN   = 25;
static const int CS_PIN   = 8;
static const int BUSY_PIN = 24;

static const unsigned char PANEL_SETTING                  = 0x00;
static const unsigned char POWER_SETTING                  = 0x01;
static const unsigned char POWER_OFF                      = 0x02;
static const unsigned char POWER_ON                       = 0x04;
static const unsigned char BOOSTER_SOFT_START             = 0x06;
static const unsigned char DEEP_SLEEP                     = 0x07;
static const unsigned char DATA_START_TRANSMISSION_1      = 0x10;
static const unsigned char DISPLAY_REFRESH                = 0x12;
static const unsigned char PLL_CONTROL                    = 0x30;
static const unsigned char TEMPERATURE_CALIBRATION        = 0x41;
static const unsigned char VCOM_AND_DATA_INTERVAL_SETTING = 0x50;
static const unsigned char TCON_SETTING                   = 0x60;
static const unsigned char TCON_RESOLUTION                = 0x61;
static const unsigned char VCM_DC_SETTING                 = 0x82;

EinkDisplay::EinkDisplay() : mInit(false) { }

EinkDisplay::~EinkDisplay()
{
    if (mInit)
    {
        sleep();
    }

    bcm2835_spi_end();
    bcm2835_close();
}

bool EinkDisplay::initialize()
{
    if (!bcm2835_init())
    {
        return false;
    }

    bcm2835_gpio_fsel(RST_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(DC_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BUSY_PIN, BCM2835_GPIO_FSEL_INPT);

    //Start spi interface, set spi pin for the reuse function
    if (!bcm2835_spi_begin())
    {
        return false;
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);    //High first transmission
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                 //spi mode 0
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128); //Frequency
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                    //set CE0
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);    //enable cs0

    reset();

    sendCommand(POWER_SETTING);
    sendData(0x37);
    sendData(0x00);

    sendCommand(PANEL_SETTING);
    sendData(0xCF);
    sendData(0x08);

    sendCommand(BOOSTER_SOFT_START);
    sendData(0xC7);
    sendData(0xCC);
    sendData(0x28);

    sendCommand(POWER_ON);
    waitUntilIdle();

    sendCommand(PLL_CONTROL);
    sendData(0x3C);

    sendCommand(TEMPERATURE_CALIBRATION);
    sendData(0x00);

    sendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    sendData(0x77);

    sendCommand(TCON_SETTING);
    sendData(0x22);

    sendCommand(TCON_RESOLUTION);
    sendData(0x02);              //source 640
    sendData(0x80);
    sendData(0x01);              //gate 384
    sendData(0x80);

    sendCommand(VCM_DC_SETTING);
    sendData(0x1E);              //decide by LUT file

    sendCommand(0xE5);           //FLASH MODE
    sendData(0x03);

    mInit = true;

    return true;
}

void EinkDisplay::display(const Citra::Display::ImageBuffer& inImageBuffer, bool inInvert /* = false */)
{
    sendCommand(DATA_START_TRANSMISSION_1);

    for (int i = 0; i < inImageBuffer.length(); i += 2)
    {
        unsigned char d = 0x00;

        if (!inInvert)
        {
            d |= 0x30 ^ inImageBuffer.at(i);
            d |= 0x03 ^ inImageBuffer.at(i+1);
        }
        else
        {
            d |= 0x30 & inImageBuffer.at(i);
            d |= 0x03 & inImageBuffer.at(i+1);
        }

        sendData(d);
    }

    sendCommand(DISPLAY_REFRESH);
    bcm2835_delay(100);
    waitUntilIdle();
}

void EinkDisplay::set(unsigned char inChar, int inNum)
{
    sendCommand(DATA_START_TRANSMISSION_1);

    for(int i = 0; i < inNum; i++)
    {
        sendData(inChar);
    }

    sendCommand(DISPLAY_REFRESH);
    bcm2835_delay(100);
    waitUntilIdle();
}

void EinkDisplay::sendCommand(unsigned char command)
{
    bcm2835_gpio_write(DC_PIN, LOW);
    bcm2835_spi_transfer(command);
}

void EinkDisplay::sendData(unsigned char data)
{
    bcm2835_gpio_write(DC_PIN, HIGH);
    bcm2835_spi_transfer(data);
}

void EinkDisplay::waitUntilIdle()
{
    while (!bcm2835_gpio_lev(BUSY_PIN)) // 0: busy, 1: idle
    {
        bcm2835_delay(100);
    }
}

void EinkDisplay::reset()
{
    bcm2835_gpio_write(RST_PIN, LOW); //module reset
    bcm2835_delay(200);
    bcm2835_gpio_write(RST_PIN, HIGH);
    bcm2835_delay(200);
}

void EinkDisplay::sleep()
{
    sendCommand(POWER_OFF);
    waitUntilIdle();
    sendCommand(DEEP_SLEEP);
    sendData(0xa5);

    mInit = false;
}

} /* namespace Display*/ } /* namespace Citra */
