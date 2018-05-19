#include <string>

#include "GPout.hpp"

namespace Citra { namespace GPIO {

// http://www.raspberrypi-spy.co.uk/2012/07/16x2-lcd-module-control-using-python/#prettyPhoto[gal_2]/3/
static const bool CMD = false;
static const bool CHR = true;

class GPlcd
{
    public:
        GPlcd(int inRegPin, int inEnaPin,
              int inDa4Pin, int inDa5Pin,
              int inDa6Pin, int inDa7Pin)
          : mRegis(inRegPin), mEnabl(inEnaPin),
            mData4(inDa4Pin), mData5(inDa5Pin),
            mData6(inDa6Pin), mData7(inDa7Pin)
        {
	        writeByte(0x33, CMD); // 110011 Initialise
	        writeByte(0x32, CMD); // 110010 Initialise
	        writeByte(0x06, CMD); // 000110 Cursor move direction
	        writeByte(0x0C, CMD); // 001100 Display On,Cursor Off, Blink Off
	        writeByte(0x28, CMD); // 101000 Data length, number of lines, font size
	        clear();
        }

        virtual ~GPlcd() { clear(); }

        void clear()
        {
            writeByte(0x01, CMD); // 000001 Clear display
        }

        void setTextLine1(const std::string& inText)
        {
	        setText(inText, 0x80);
        }
  
        void setTextLine2(const std::string& inText)
        {
	        setText(inText, 0xC0);
        }

    protected:
        void setText(const std::string& inText, char inLine)
        {
            writeByte(inLine, CMD);

            for (const char& c : inText)
            {
                writeByte(c, CHR);
            }
        }

        void writeByte(const char& inByte, bool inMode)
        {
            mRegis.setOn(inMode);
    
            // High bits
            mData4.setOn(inByte & 0x10); 
            mData5.setOn(inByte & 0x20); 
            mData6.setOn(inByte & 0x40); 
            mData7.setOn(inByte & 0x80); 

            // Toggle 'Enable' pin
            toggleEnable();

            // Low bits
            mData4.setOn(inByte & 0x01); 
            mData5.setOn(inByte & 0x02); 
            mData6.setOn(inByte & 0x04); 
            mData7.setOn(inByte & 0x08); 

            // Toggle 'Enable' pin
            toggleEnable();
        }

        void toggleEnable()
        {
	        //usleep(5);
            mEnabl.on();
            //usleep(5);
            mEnabl.off();
            //usleep(5);
        }
  
        GPout mRegis;
        GPout mEnabl;
        GPout mData4;
        GPout mData5;
        GPout mData6;
        GPout mData7;
};

} /* namespace GPIO */ } /* namespace Citra */
