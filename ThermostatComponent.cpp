#include "ThermostatComponent.h"

namespace thermostat {

ThermostatComponent::ThermostatComponent()
  : mShutdown(false),
    mSetPointController(SetPointController),
    mThermometer(Thermometer),
    mControlAlgorithm(ControlAlgorithm),
    mThermalController(ThermalController),
    mThermostatDisplayList()
{
    for (const std::string& aModule : ThermostatDisplays)
    {
        Module<thermostat::Interfaces::IThermostatDisplay> aDisplay(aModule);
        mThermostatDisplayList.push_back(aDisplay);
    }
}

ThermostatComponent::~ThermostatComponent() { }

void ThermostatComponent::shutdown()
{
    mShutdown = true;
}

void ThermostatComponent::run()
{
    while (!mShutdown)
    {
	bool control = mSetPointController->isSetPointDefined();

	Interfaces::Control action = Interfaces::STAY;

        float setpoint = mSetPointController->currentSetPointFahrenheit();

        float currentTemp = mThermometer->currentTemperatureFahrenheit();

        if (control)
	{
	    action = mControlAlgorithm->controlTemperatureFahrenheit(setpoint, currentTemp);
	}

        switch (action)
        {
	    case Interfaces::STAY:
	    {
	        mThermalController->stay();
	        break;
	    }
            case Interfaces::HEAT:
            {
	        mThermalController->heat();
                break;
            }
            case Interfaces::COOL:
	    {
	        mThermalController->cool();
                break;
            }
        }

        for (Module<Interfaces::IThermostatDisplay>& aDisplayPtr : mThermostatDisplayList)
	{
            aDisplayPtr->display(control, setpoint, currentTemp, action); 
	}

        usleep(100000); // 100ms 
    }
}

} /* namespace thermostat */
