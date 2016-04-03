#ifndef _I_THERMAL_CONTROLLER_H_
#define _I_THERMAL_CONTROLLER_H_

namespace thermostat { namespace Interfaces {

class IThermalController
{
    public:
        IThermalController() {}
        virtual ~IThermalController() {}

        virtual void heat() = 0;
        virtual void cool() = 0;
        virtual void stay() = 0;

};

} /* namespace Interfaces*/ } /* namespace thermostat */

#endif /* _I_THERMAL_CONTROLLER_H_ */
