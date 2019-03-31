#include <mlbClock/Interfaces/iMlbDataGrabber.h>
#include <mlbClock/Interfaces/iMlbImageBuilder.h>

#include <Module/Module.hpp>

#include <iostream>

#include <QtGui/QtGui>

int main(int argc, char* argv[])
{
    std::cout << "Running " << argv[0] << std::endl;

    std::string aTeam = "PHI";

    if (argc > 1)
    {
        aTeam = std::string(argv[1]);
    }

    QApplication app(argc, argv);

    Citra::Module<Citra::mlbClock::Interfaces::iMlbDataGrabber> mDataGrabber("./lib/XmlDataGrabber.so");
    Citra::Module<Citra::mlbClock::Interfaces::iMlbImageBuilder> mImageBuilder("./lib/CairoMlbImageBuilder.so");

    std::vector<Citra::mlbClock::mlbGame> games = mDataGrabber->getGames(aTeam);

    Citra::Display::ImageBuffer aImgBuf = mImageBuilder->buildImage(aTeam, games);

    QImage aImage(aImgBuf.width(), aImgBuf.height(), QImage::Format_Mono);

    for (int y = 0; y < aImgBuf.height(); y++)
    {
        for (int x = 0; x < aImgBuf.width(); x++)
        {
            aImage.setPixel(x, y, (aImgBuf.at(x,y) & 0xFF ? 0 : 1));
        }
    }

    QGraphicsScene* scene = new QGraphicsScene(0, 0, aImgBuf.width(), aImgBuf.height());
    QGraphicsView* view = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(aImage));
    scene->addItem(item);
    view->show();

    int exitCode = app.exec();
    std::cout << "(DONE)" << std::endl;
    return exitCode;
}
