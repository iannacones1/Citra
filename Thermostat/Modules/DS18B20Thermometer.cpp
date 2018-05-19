#include <string>
#include <ctype.h>
#include <fstream>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include <Thermostat/Interfaces/IThermometer.h>
#include <Module/create_module_macro.h>

namespace Citra { namespace Thermostat {

class DS18B20Thermometer : public Interfaces::IThermometer
{
    public:
        DS18B20Thermometer() : Interfaces::IThermometer(),
                               mDeviceId("28-000006b6342e"),
                               mTempMutex(),
                               mCurrentTemp(0.0),
                               mThread(boost::bind(&DS18B20Thermometer::runThread, this))
        { }

        virtual ~DS18B20Thermometer()
        { 
	        mThread.interrupt();
	        mThread.join();
        }

        virtual float currentTemperatureFahrenheit()
        { 
            boost::mutex::scoped_lock aLock(mTempMutex);
	        return mCurrentTemp;
	    }

        void runThread()
        {
	        while (!mThread.interruption_requested())
	        {
                float newTemp = this->getTemp();

		        {
		            boost::mutex::scoped_lock aLock(mTempMutex);
	                mCurrentTemp = newTemp;
		        }

		        static boost::posix_time::milliseconds sleepTime(1000);

                boost::this_thread::sleep(sleepTime);
	        }
        }

    protected:
        float getTemp()
        { 
            // https://learn.adafruit.com/adafruits-raspberry-pi-lesson-11-ds18b20-temperature-sensing/hardware 
            static std::string aFileName = "/sys/bus/w1/devices/" + mDeviceId + "/w1_slave";
	    
            std::ifstream aFile(aFileName.c_str());
    
	        if (!aFile.is_open())
            {
	            std::cerr << "Cannot read DS18B20 Device: " << mDeviceId << std::endl;
                return 0.0; // nan?
	        }

	        std::string aLine;

            getline(aFile, aLine);

	        std::string status = aLine.substr(aLine.find_last_of(" ") + 1, std::string::npos);

            if (status != "YES")
	        {
                std::cerr << "DS18B20 Device: " << mDeviceId << " disconnected" << std::endl;
                return 0.0; // nan?
	        }

            getline(aFile, aLine);
	    
            aFile.close();
            
	        float temp = std::stof(aLine.substr(aLine.find_last_of("=") + 1, std::string::npos));

            return (temp * 0.0018 + 32);
        }

        std::string mDeviceId;
        boost::mutex mTempMutex;
        float mCurrentTemp;
        boost::thread mThread;
};

MODULE(Interfaces::IThermometer, DS18B20Thermometer)

} /* namespace Thermostat*/ } /* namespace Citra */
