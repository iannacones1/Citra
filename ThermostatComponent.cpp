#include "ThermostatComponent.h"

namespace thermostat {

ThermostatComponent::ThermostatComponent(Interfaces::ISetPointController* inSetPointController,
                                         Interfaces::IThermometer* inThermometer,
					 Interfaces::ITemperatureControlAlgorithm* inControlAlgorithm,
                                         Interfaces::IThermalController* inThermalController,
                                         Interfaces::IThermostatDisplay* inThermostatDisplay)
  : mShutdown(false),
    mSetPointController(inSetPointController),
    mThermometer(inThermometer),
    mControlAlgorithm(inControlAlgorithm),
    mThermalController(inThermalController),
    mThermostatDisplay(inThermostatDisplay)
{
    std::cout << __func__ << std::endl; 
}

ThermostatComponent::~ThermostatComponent()
{
    std::cout << __func__ << std::endl; 
}

void ThermostatComponent::run()
{
    while (!mShutdown)
    {
        std::cout << "---" << __func__ << "---" << std::endl;

	bool control = mSetPointController->isSetPointDefined();

        std::cout << " Control Temp = " << (control ? "ON" : "OFF") << std::endl;

        float setpoint;
        float currentTemp;
	Interfaces::Control action;

        if (control)
	{
	    setpoint = mSetPointController->currentSetPointFahrenheit();
            currentTemp = mThermometer->currentTemperatureFahrenheit();
	    action = mControlAlgorithm->controlTemperatureFahrenheit(setpoint, currentTemp);

	    std::cout << "Setpoint Temp = " << setpoint << std::endl;
	    std::cout << " Current Temp = " << currentTemp << std::endl;
	    std::cout << "  Action Temp = ";

	    switch (action)
	    {
	        case Interfaces::STAY :
		{
		    mThermalController->stay();
                    std::cout << "STAY";
                    break;
		}
	        case Interfaces::HEAT :
                {
		    mThermalController->heat();
                    std::cout << "HEAT";

                    break;
		}
	        case Interfaces::COOL :
		{
		    mThermalController->cool();
                    std::cout << "COOL";
                    break;
		}
	    }

	    std::cout << std::endl;
	}

	mThermostatDisplay->display(control, setpoint, currentTemp, action); 

        sleep(1);
    }
}

void ThermostatComponent::shutdown()
{
    std::cout << __func__ << std::endl; 
    mShutdown = true;
}

} /* namespace thermostat */
