#ifndef _DAY_SUMMARY_GRAPHICS_ITEM_HPP_
#define _DAY_SUMMARY_GRAPHICS_ITEM_HPP_

#include <QtGui/QtGui>

namespace Citra { namespace mlbClock {

static const int BOX_WIDTH  = 640/5;
static const int BOX_HEIGHT = BOX_WIDTH * 0.75;

class daySummaryGraphicsItem : public QGraphicsItem
{
  public:
    daySummaryGraphicsItem(int x, int y, const mlbGame& inGame, const std::string& inTeam, bool inFrame = true) : mGame(inGame), mTeam(inTeam), mFrame(inFrame)
    {
        this->setPos(x,y);
    }

    virtual ~daySummaryGraphicsItem() { }

    virtual QRectF boundingRect() const
    {
        return QRectF(0, 0, BOX_WIDTH, BOX_HEIGHT);
    }

    int width()  const { return boundingRect().width();  }
    int height() const { return boundingRect().height(); }

    virtual void paint(QPainter* inPainter, const QStyleOptionGraphicsItem* /* Option */, QWidget* /* inWidget */)
    {
        inPainter->setFont(QFont("lato", 10));

        if (mFrame)
        {
            inPainter->drawRect(0, 0, BOX_WIDTH, BOX_HEIGHT);
        }
        else
        {
            inPainter->drawRect(0, 0, BOX_WIDTH, 0);
        }

        {
            QRectF rect(5, 5, BOX_WIDTH/2 - 5, 23);
            inPainter->drawText(rect, Qt::AlignLeft, QString::fromStdString(mGame.Day));
        }

        {
            QRectF rect(BOX_WIDTH/2, 5, BOX_WIDTH/2 - 5, 23);
            inPainter->drawText(rect, Qt::AlignRight, QString::number(mGame.num));
        }


        {
            QRectF rect(0, BOX_HEIGHT - 28, BOX_WIDTH, 23);

            if (mGame.status == "Final")
            {
                inPainter->drawText(rect, Qt::AlignCenter, QString::fromStdString(mGame.finalScore(mTeam)));
            }
            else if (mGame.status == "In Progress")
            {
                inPainter->drawText(rect, Qt::AlignCenter, QString("LIVE"));
            }
            else
            {
                inPainter->drawText(rect, Qt::AlignCenter, QString::fromStdString(mGame.teamTime(mTeam)));
            }

        }

        QRectF rect(0, 0, BOX_WIDTH, BOX_HEIGHT);

        inPainter->setFont(QFont("lato", 22));

        if (mGame.home().isNamed(mTeam))
        {
            inPainter->drawText(rect, Qt::AlignCenter, QString::fromStdString(mGame.away().name_abbrev));
        }
        else
        {
            inPainter->drawText(rect, Qt::AlignCenter, QString::fromStdString("@" + mGame.home().name_abbrev));
        }


    }

protected:
    mlbGame mGame;
    std::string mTeam;
    bool mFrame;
};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _DAY_SUMMARY_GRAPHICS_ITEM_HPP_ */
