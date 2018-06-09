#include <algorithm>
#include <QtGui/QtGui>

static const int SPACEING    = 30;
static const int FONT_HEIGHT = 23;

namespace Citra { namespace mlbClock {

class linescoreGraphicsItem : public QGraphicsItem
{
public:
    linescoreGraphicsItem(const game& inGame) : mGame(inGame), mInningCount(std::max(mGame.away().innings.size(), (size_t)9)) { }
    virtual ~linescoreGraphicsItem() { }

    virtual QRectF boundingRect() const
    {
        float w = 0;
        w += SPACEING * 1.5;          // Team names
        w += SPACEING * mInningCount; // inning scores
        w += SPACEING * 3.25;         // R H E

        if (!mGame.isOver())
        {
            w += FONT_HEIGHT * 3;         // Basescores
        }

        float rows = 3;

        if (mGame.winning_pitcher || mGame.losing_pitcher)
        {
            rows++;
        }

        if (mGame.save_pitcher)
        {
            rows++;
        }

        return QRectF(0, 0, w, FONT_HEIGHT * rows);
    }

    int width()  const { return boundingRect().width();  }
    int height() const { return boundingRect().height(); }

    virtual void paint(QPainter* inPainter, const QStyleOptionGraphicsItem* /* Option */, QWidget* /* inWidget */)
    {
        inPainter->setFont(QFont("lato", 14, QFont::Bold));

        int x = SPACEING * 1.5;
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

        if (mGame.inning && mGame.inning_state)
        {
            int yLoc = (mGame.inning_state.get() == "Top" ? y : y + FONT_HEIGHT);

            QRectF rect(x + (SPACEING * (mGame.inning.get() - 1)), yLoc, SPACEING, FONT_HEIGHT);
            inPainter->drawRect(rect);
        }

        BOOST_FOREACH(const team& aTeam, mGame.teams)
        {
            x = 0;

            inPainter->setFont(QFont("lato", 14, QFont::Bold));

            QRectF rect(x, y, SPACEING * 1.5, FONT_HEIGHT);
            inPainter->drawText(rect, Qt::AlignVCenter, QString::fromStdString(aTeam.name_abbrev));
            x += rect.width();

            inPainter->setFont(QFont("lato", 14));

            for (size_t i = 0; i < mInningCount; i++)
            {
                if (i < aTeam.innings.size())
                {
                    addText(inPainter, x, y, aTeam.innings.at(i));
                }
                else if (mGame.isOver())
                {
                    addText(inPainter, x, y, std::string("X"));
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

        int h = FONT_HEIGHT * 3;

        if (!mGame.isOver())
        {
            addDiamond(inPainter, x + h * 0.25, h/2, h/4 - 4);
            addDiamond(inPainter, x + h * 0.50, h/4, h/4 - 4);
            addDiamond(inPainter, x + h * 0.75, h/2, h/4 - 4);

            inPainter->setFont(QFont("lato", 10));
            QRectF rect(x, FONT_HEIGHT * 2 , h, FONT_HEIGHT);
            inPainter->drawText(rect, Qt::AlignCenter, QString::fromStdString(mGame.BSO()));
        }

        {
            std::stringstream ss;

            if (mGame.winning_pitcher)
            {
                ss << " W: " << mGame.winning_pitcher.get().winSummary();
            }

            if (mGame.losing_pitcher)
            {
                ss << " L: " << mGame.losing_pitcher.get().winSummary();
            }

            if (mGame.winning_pitcher || mGame.losing_pitcher)
            {
                QRectF rect(0, y, x, FONT_HEIGHT);
                inPainter->setFont(QFont("lato", 10));
                inPainter->drawText(rect, Qt::AlignLeft, QString::fromStdString(ss.str()));
                y += FONT_HEIGHT;
            }
        }

        {
            std::stringstream ss;

            if (mGame.save_pitcher)
            {
                ss << " S: " << mGame.save_pitcher.get().saveSummary();

                QRectF rect(0, y, x, FONT_HEIGHT);
                inPainter->setFont(QFont("lato", 10));
                inPainter->drawText(rect, Qt::AlignLeft, QString::fromStdString(ss.str()));
                y += FONT_HEIGHT;
            }
        }

    }

    void addDiamond(QPainter* inPainter, int x, int y, int r)
    {
        QPolygonF outLine;
        outLine << QPointF(x    , y - r);
        outLine << QPointF(x + r, y    );
        outLine << QPointF(x    , y + r);
        outLine << QPointF(x - r, y);

        QBrush aBrush = inPainter->brush();
        aBrush.setColor(Qt::black);
        inPainter->setBrush(aBrush);

        inPainter->drawPolygon(outLine);
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

    void addText(QPainter* inPainter, int& x, int& y, int inText)
    {
        addText(inPainter, x, y, QString::number(inText));
    }

protected:
    game mGame;
    size_t mInningCount;
};

} /* namespace mlbClock */ } /* namespace Citra */
