#include "mlbClockComponent.h"

#include <iomanip>
#include <unistd.h>
#include <boost/foreach.hpp>

#include "XmlDataGrabber.hpp"
#include <Display/EinkDisplay.h>

#include "linescoreGraphicsItem.hpp"
#include "daySummaryGraphicsItem.hpp"

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
    int val = inColor.red() + inColor.green() + inColor.blue();

    int breakVal = 255 * 3 / 2;
    
    return (val < breakVal ? 0x00 : 0xFF);
    //return (inColor != Qt::white ? 0x00 : 0xFF);
    //return (inColor == Qt::black ? 0x00 : 0xFF);
}

void mlbClockComponent::run()
{
//    int z = 0;

    Display::EinkDisplay epd;
    if (!epd.initialize())
    {
        std::cerr << "e-Paper init failed" << std::endl;
        return;
    }

    std::vector<game> games = DataGrabber::getGames("PHI");

//    for (size_t focalGame = 0; !mShutdown && focalGame < games.size(); focalGame++)
    {
        size_t focalGame = (games.at(2).status == "Preview" ? 1 : 2);


    game cGame = games.at(focalGame);

    QGraphicsScene* scene = new QGraphicsScene(0, 0, W, H);

    QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, W, H);
    background->setPen(QPen((Qt::white)));
    background->setBrush(QBrush((Qt::white)));
    scene->addItem(background);

    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(QString::fromStdString("../" + cGame.home().name_abbrev + ".bmp"))));
        item->setPos(0, H);
        item->moveBy(0, -(item->boundingRect().height()));
        scene->addItem(item);
    }

    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(QString::fromStdString("../" + cGame.away().name_abbrev + ".bmp"))));
        item->setPos(W, H);
        item->moveBy(-(item->boundingRect().width()), -(item->boundingRect().height()));
        scene->addItem(item);
    }

    for (size_t i = 0; i < games.size(); i++)
    {
        int offset = (i > focalGame ? 1 : 0);
        scene->addItem(new daySummaryGraphicsItem((W/5) * i - offset, 0, games.at(i), i != focalGame));
    }

    linescoreGraphicsItem* aLinescore = new linescoreGraphicsItem(cGame);
    aLinescore->setPos(W/2, H/2);
    aLinescore->moveBy(-aLinescore->width()/2, -aLinescore->height()/2);
    scene->addItem(aLinescore);

    {
        QGraphicsTextItem* aPtr = new QGraphicsTextItem(QString::fromStdString(cGame.status));
        aPtr->setPos(10, (W/5) + 10);
        scene->addItem(aPtr);
    }

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

    sleep(10);
    }
}

} /* namespace mlbClock */ } /* namespace Citra */
