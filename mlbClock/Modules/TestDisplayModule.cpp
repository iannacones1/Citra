#include <QtGui/QtGui>

#include <Module/create_module_macro.h>

#include <Display/Interfaces/iBufferDisplay.h>

namespace Citra { namespace Display {

class TestDisplayModule : public Interfaces::iBufferDisplay
{
    public:
        TestDisplayModule() : Interfaces::iBufferDisplay()
        { }

        virtual ~TestDisplayModule() { }

        virtual void display(const ImageBuffer& inBuffer)
        {
            QApplication app(0, 0);

            QImage aImage(inBuffer.width(), inBuffer.height(), QImage::Format_Mono);

            for (int y = 0; y < inBuffer.height(); y++)
            {
                for (int x = 0; x < inBuffer.width(); x++)
                {
                    aImage.setPixel(x, y, (inBuffer.at(x,y) & 0xFF ? 0 : 1));
                }
            }

            QGraphicsScene* scene = new QGraphicsScene(0, 0, inBuffer.width(), inBuffer.height());
            QGraphicsView* view = new QGraphicsView(scene);
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(aImage));
            scene->addItem(item);
            view->show();

            app.exec();
        }
};

MODULE(Interfaces::iBufferDisplay, TestDisplayModule)

} /* namespace Display*/ } /* namespace Citra */
