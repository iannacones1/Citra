#include "ThermostatComponent.h"

namespace thermostat {

ThermostatComponent::ThermostatComponent(Interfaces::ISetPointController* inSetPointController,
                                         Interfaces::IThermometer* inThermometer,
					 Interfaces::ITemperatureControlAlgorithm* inControlAlgorithm)
  : mShutdown(false),
    mSetPointController(inSetPointController),
    mThermometer(inThermometer),
    mControlAlgorithm(inControlAlgorithm)
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

        if (control)
	{
	    float setpoint = mSetPointController->currentSetPointFahrenheit();
            float currentTemp = mThermometer->currentTemperatureFahrenheit();
	    Interfaces::Control action = mControlAlgorithm->controlTemperatureFahrenheit(setpoint, currentTemp);

	    std::cout << "Setpoint Temp = " << setpoint << std::endl;
	    std::cout << " Current Temp = " << currentTemp << std::endl;
	    std::cout << "  Action Temp = ";

	    switch (action)
	    {
	        case Interfaces::STAY : std::cout << "STAY"; break;
	        case Interfaces::HEAT : std::cout << "HEAT"; break;
	        case Interfaces::COOL : std::cout << "COOL"; break;
	    }

	    std::cout << std::endl;
	}

        sleep(1);
    }
}

void ThermostatComponent::shutdown()
{
    std::cout << __func__ << std::endl; 
    mShutdown = true;
}

} /* namespace thermostat */
