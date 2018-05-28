#include "mlbClockComponent.h"

#include <iomanip>
#include <unistd.h>
#include <boost/foreach.hpp>

#include "DataGrabber.hpp"
#include <Display/EinkDisplay.h>

#include "linescoreGraphicsItem.hpp"

namespace Citra { namespace mlbClock {

static const int W = Citra::Display::ImageBuffer::WIDTH;
static const int H = Citra::Display::ImageBuffer::HEIGHT;

mlbClockComponent::mlbClockComponent() : mShutdown(false) { }

mlbClockComponent::~mlbClockComponent() { }

void mlbClockComponent::shutdown()
{
    mShutdown = true;
}

unsigned char mask(const QColor& inColor)
{
    return (inColor != Qt::white ? 0x00 : 0xFF);
}

void mlbClockComponent::run()
{
    int z = 0;

    Display::EinkDisplay epd;
    if (!epd.initialize())
    {
        std::cerr << "e-Paper init failed" << std::endl;
        return;
    }

    std::list<game> aGames = DataGrabber::getGames();

    while (!mShutdown)
    {
        QGraphicsScene* scene = new QGraphicsScene(0, 0, W, H);

        QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, W, H);
        background->setPen(QPen((Qt::white)));
        background->setBrush(QBrush((Qt::white)));
        scene->addItem(background);

        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage("../phillies_p.bmp")));
        scene->addItem(item);

        BOOST_FOREACH(const game& aGame, aGames)
        {
            if (aGame.containsTeam("PHI"))
            {
                linescoreGraphicsItem* aLinescore = new linescoreGraphicsItem(aGame);
                aLinescore->setPos(W/2, H/2);
                aLinescore->moveBy(-aLinescore->width()/2, 0);
                scene->addItem(aLinescore);
            }
        }

        scene->addItem(new QGraphicsTextItem(QString::number(z++)));

        QImage aImage(W, H, QImage::Format_RGB32);
        QPainter painter(&aImage);
        scene->render(&painter);

        Citra::Display::ImageBuffer aImgBuf;

        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x += 2)
            {
                unsigned char d = 0x00;

                d |= 0x30 & mask(aImage.pixel(x    , y));
                d |= 0x03 & mask(aImage.pixel(x + 1, y));

                aImgBuf.set(x/2, y, d);
            }
        }

        epd.display(aImgBuf);
    }
}

} /* namespace mlbClock */ } /* namespace Citra */
