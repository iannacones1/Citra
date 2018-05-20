#include "mlbClockComponent.h"

#include <iomanip>
#include <unistd.h>
#include <boost/foreach.hpp>

#include "DataGrabber.hpp"

static const int W = 640;
static const int H = 384;
static const int space = 40;

namespace Citra { namespace mlbClock {

mlbClockComponent::mlbClockComponent() : mShutdown(false) { }

mlbClockComponent::~mlbClockComponent() { }

void mlbClockComponent::shutdown()
{
    mShutdown = true;
}

void mlbClockComponent::addText(int& x, int& y, const QString& inText, QGraphicsScene* scene)
{
    QGraphicsTextItem* textItem = new QGraphicsTextItem(inText);
    textItem->setPos(y, x);
    scene->addItem(textItem);
    y += space/2;

    textItem->moveBy(-textItem->boundingRect().width()/2, 0);
}

void mlbClockComponent::addText(int& x, int& y, const std::string& inText, QGraphicsScene* scene)
{
	addText(x, y, QString::fromStdString(inText), scene);
}

void mlbClockComponent::run()
{
//    while (!mShutdown)
//    {
	      std::list<game> aGames = DataGrabber::getGames();

          QGraphicsScene* scene = new QGraphicsScene(0, 0, W, H);
          QGraphicsView* view = new QGraphicsView(scene);

          QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("../phillies_p.bmp")));
	      scene->addItem(item);


	      BOOST_FOREACH(const game& aGame, aGames)
	      {
	    	  if (aGame.containsTeam("PHI"))
	    	  {
                  int x = 150;
            	  int y = 150 + space;
            	  int h = 23;

            	  size_t numIn = std::max(aGame.away().innings.size(), (size_t)9);
                  for (size_t i = 0; i < numIn; i++)
                  {
                	  addText(x, y, QString::number(i + 1), scene);
                  }

                  y += (space/4);

                  addText(x, y, QString("R"), scene);
                  addText(x, y, QString("H"), scene);
                  addText(x, y, QString("E"), scene);

		          x += h;

                  BOOST_FOREACH(const team& aTeam, aGame.teams)
	    	      {
                	  y = 150;

                      addText(x, y, aTeam.name_abbrev, scene);

                      y += space/2;

//			          BOOST_FOREACH(const std::string& aRun, aTeam.innings)
//			          {
//	                      addText(x, y, aRun, scene);
//                      }

                      for (size_t i = 0; i < numIn; i++)
                      {
                    	  if (i < aTeam.innings.size())
                    	  {
                    		  addText(x, y, aTeam.innings[i], scene);
                    	  }
                    	  else
                    	  {
                    		    y += space/2;
                    	  }
                      }

			          y += (space/4);

                      addText(x, y, QString::number(aTeam.runs), scene);
                      addText(x, y, QString::number(aTeam.hits), scene);
                      addText(x, y, QString::number(aTeam.errors), scene);

			          x += h;
	    	      }
		          std::cout << std::endl;
	    	  }
	      }

	      view->show();

//        sleep(1);
//    }
}

} /* namespace mlbClock */ } /* namespace Citra */
