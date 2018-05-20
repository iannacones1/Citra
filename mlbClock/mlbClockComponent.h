#ifndef _MLB_CLOCK_COMPONENT_H_
#define _MLB_CLOCK_COMPONENT_H_

#include <QtGui/QtGui>

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

        bool mShutdown;
};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _MLB_CLOCK_COMPONENT_H_ */
