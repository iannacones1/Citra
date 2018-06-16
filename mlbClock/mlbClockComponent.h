#ifndef _MLB_CLOCK_COMPONENT_H_
#define _MLB_CLOCK_COMPONENT_H_

#include <string>

#include <QtGui/QtGui>

#include <Display/Interfaces/iBufferDisplay.h>

#include <Module/Module.hpp>
#include <Configurable/Configurable.hpp>

namespace Citra { namespace mlbClock {

class mlbClockComponent
{
    public:
	    mlbClockComponent();
        virtual ~mlbClockComponent();

        void run();
        void shutdown();

    protected:
        void addText(int& x, int& y, const QString& inText,     QGraphicsScene* scene);
        void addText(int& x, int& y, const std::string& inText, QGraphicsScene* scene);

        CONFIGURABLE
        (
            (std::string) DisplayModule,
            (std::string) TEAM
        )

        INITIALIZE(mlbClockComponent)

        bool mShutdown;
        Module<Display::Interfaces::iBufferDisplay> mDisplay;
};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _MLB_CLOCK_COMPONENT_H_ */
