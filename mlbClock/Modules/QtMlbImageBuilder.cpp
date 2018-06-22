
#include <mlbClock/Interfaces/iMlbImageBuilder.h>

#include <mlbClock/GraphicsItems/linescoreGraphicsItem.hpp>
#include <mlbClock/GraphicsItems/PreviewGraphicsItem.hpp>
#include <mlbClock/GraphicsItems/daySummaryGraphicsItem.hpp>

#include <Module/create_module_macro.h>

#include <QtGui/QtGui>

#include <iostream>

namespace Citra { namespace mlbClock {

static const int W = 640;
static const int H = 384;

class QtMlbImageBuilder : public Interfaces::iMlbImageBuilder
{
  public:
    QtMlbImageBuilder() : Interfaces::iMlbImageBuilder(),
                          mQApplication(NULL)
    {
        if (QCoreApplication::instance() == NULL)
        {
            std::cout << __func__ << " creating QApplication" << std::endl;
            int argc(0);
            char* argv[10];
            mQApplication = new QApplication(argc, argv);
        }
    }

    virtual ~QtMlbImageBuilder() { }

    unsigned char mask(const QColor& inColor)
    {
        int val = inColor.red() + inColor.green() + inColor.blue();

        int breakVal = 255 * 3 / 2;

        return (val < breakVal ? 0x00 : 0xFF);
    }

    virtual Display::ImageBuffer buildImage(const std::string& inTeam, const std::vector<mlbGame>& inGameList)
    {
        size_t focalGame = (inGameList.at(2).status == "Preview" ? 1 : 2);

        mlbGame cGame = inGameList.at(focalGame);

        // OK the goal is for mlbClock to run as a daemon which means I can't use QGraphicsScene
        //  because it relies on QApplication which cannot run headless; there are also issues with
        // https://www.x.org/archive/X11R7.7/doc/man/man1/Xvfb.1.xhtml
        QGraphicsScene* scene = new QGraphicsScene(0, 0, W, H);

        QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, W, H);
        background->setPen(QPen((Qt::white)));
        background->setBrush(QBrush((Qt::white)));
        scene->addItem(background);

        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(QString::fromStdString("../data/MLB/" + cGame.home().name_abbrev + ".jpg"))));
            item->setPos(0, H);
            item->moveBy(0, -(item->boundingRect().height()));
            scene->addItem(item);
        }

        {
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(QString::fromStdString("../data/MLB/" + cGame.away().name_abbrev + ".jpg"))));
            item->setPos(W, H);
            item->moveBy(-(item->boundingRect().width()), -(item->boundingRect().height()));
            scene->addItem(item);
        }

        for (size_t i = 0; i < inGameList.size(); i++)
        {
            int offset = (i > focalGame ? 1 : 0);
            scene->addItem(new daySummaryGraphicsItem((W/5) * i - offset, 0, inGameList.at(i), inTeam, i != focalGame));
        }

        if (cGame.status == "Preview"  ||
            cGame.status == "Pre-Game" ||
            cGame.status == "Warmup")
        {
            PreviewGraphicsItem* aLinescore = new PreviewGraphicsItem(cGame);
            aLinescore->setPos(W/2, H/2);
            aLinescore->moveBy(-aLinescore->width()/2, -aLinescore->height()/2);
            scene->addItem(aLinescore);
        }
        else
        {
            linescoreGraphicsItem* aLinescore = new linescoreGraphicsItem(cGame);
            aLinescore->setPos(W/2, H/2);
            aLinescore->moveBy(-aLinescore->width()/2, -aLinescore->height()/2);
            scene->addItem(aLinescore);
        }

        { // Game Status
            std::stringstream ss;

            if (cGame.inning && cGame.inning_state)
            {
                ss << cGame.inning_state.get() << " " << cGame.inning.get();
            }
            else
            {
                ss << cGame.status;
            }
            QGraphicsTextItem* aPtr = new QGraphicsTextItem(QString::fromStdString(ss.str()));
            aPtr->setPos(10, BOX_HEIGHT + 10);
            scene->addItem(aPtr);
        }

        //            if (cGame.pbp)
        //            {
        //                QGraphicsTextItem* aPtr = new QGraphicsTextItem(QString::fromStdString(cGame.pbp.get()));
        //                aPtr->setPos(W/2, H);
        //                aPtr->moveBy(-aPtr->boundingRect().width()/2, -aPtr->boundingRect().height());
        //                scene->addItem(aPtr);
        //            }

        QImage aImage(W, H, QImage::Format_RGB32);
        QPainter painter(&aImage);
        scene->render(&painter);

        Citra::Display::ImageBuffer aImgBuf(W, H);

        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                aImgBuf.set(x, y, mask(aImage.pixel(x, y)));
            }
        }

        return aImgBuf;
    }

  protected:
    QApplication* mQApplication;

};

MODULE(Interfaces::iMlbImageBuilder, QtMlbImageBuilder)

} /* namespace mlbClock */ } /* namespace Citra */
