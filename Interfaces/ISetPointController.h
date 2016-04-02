#ifndef _I_SET_POINT_CONTROLLER_H_
#define _I_SET_POINT_CONTROLLER_H_

namespace thermostat { namespace Interfaces {

class ISetPointController
{
    public:
        ISetPointController() {}
        virtual ~ISetPointController() {}

        virtual bool isSetPointDefined() = 0;
        virtual float currentSetPointFahrenheit() = 0;

};

} /* namespace Interfaces*/ } /* namespace thermostat */

#endif /* _I_SET_POINT_CONTROLLER_H_ */
