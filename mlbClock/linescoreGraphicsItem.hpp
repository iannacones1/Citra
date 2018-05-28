#include <algorithm>
#include <QtGui/QtGui>

static const int SPACEING    = 30;
static const int FONT_HEIGHT = 23;

namespace Citra { namespace mlbClock {

class linescoreGraphicsItem : public QGraphicsItem
{
public:
    linescoreGraphicsItem(const game& inGame) : mGame(inGame), mInningCount(std::min(mGame.away().innings.size(), (size_t)9)) { }
    virtual ~linescoreGraphicsItem() { }

    virtual QRectF boundingRect() const
    {
        float w = 0;
        w += SPACEING * 1.25;         // Team names
        w += SPACEING * mInningCount; // inning scores
        w += SPACEING * 3.25;          // R H E
        return QRectF(0, 0, w, FONT_HEIGHT * 3);
    }

    int width()  const { return boundingRect().width();  }
    int height() const { return boundingRect().height(); }

    virtual void paint(QPainter* inPainter, const QStyleOptionGraphicsItem* /* Option */, QWidget* /* inWidget */)
    {
        int x = SPACEING * 1.25;
        int y = 0;

        for (size_t i = 0; i < mInningCount; i++)
        {
            addText(inPainter, x, y, QString::number(i + 1));
        }

        x += (SPACEING/4);

        addText(inPainter, x, y, QString("R"));
        addText(inPainter, x, y, QString("H"));
        addText(inPainter, x, y, QString("E"));

        y += FONT_HEIGHT;

        BOOST_FOREACH(const team& aTeam, mGame.teams)
        {
            x = 0;

            QRectF rect(x, y, SPACEING * 1.25, FONT_HEIGHT);
            inPainter->drawText(rect, Qt::AlignVCenter, QString::fromStdString(aTeam.name_abbrev));
            x += rect.width();

            for (size_t i = 0; i < mInningCount; i++)
            {
                if (i < aTeam.innings.size())
                {
                    addText(inPainter, x, y, aTeam.innings[i]);
                }
                else
                {
                    x += SPACEING;
                }

            }

            x += (SPACEING/4);

            addText(inPainter, x, y, QString::number(aTeam.runs));
            addText(inPainter, x, y, QString::number(aTeam.hits));
            addText(inPainter, x, y, QString::number(aTeam.errors));

            y += FONT_HEIGHT;
        }
    }

    void addText(QPainter* inPainter, int& x, int& y, const QString& inText)
    {
        QRectF rect(x, y, SPACEING, FONT_HEIGHT);

        inPainter->drawText(rect, Qt::AlignCenter, inText);

        x += rect.width();
    }

    void addText(QPainter* inPainter, int& x, int& y, const std::string& inText)
    {
        addText(inPainter, x, y, QString::fromStdString(inText));
    }

protected:
    game mGame;
    size_t mInningCount;
};

} /* namespace mlbClock */ } /* namespace Citra */
