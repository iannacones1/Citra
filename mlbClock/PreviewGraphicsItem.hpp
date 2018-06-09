#ifndef _PREVIEW_GRAPHICS_ITEM_HPP_
#define _PREVIEW_GRAPHICS_ITEM_HPP_

#include <algorithm>
#include <QtGui/QtGui>

//static const int FONT_HEIGHT = 23;

namespace Citra { namespace mlbClock {

class PreviewGraphicsItem : public QGraphicsItem
{
public:
    PreviewGraphicsItem(const game& inGame) : mGame(inGame)
    {
        mTeamName = QFont("lato", 16, QFont::Bold);
        mPitcher = QFont("lato", 16);
        mTeamScore = QFont("lato", 12);

    }
    virtual ~PreviewGraphicsItem() { }

    virtual QRectF boundingRect() const
    {
        return QRectF(0, 0, 325, (QFontMetrics(mTeamName).height() + QFontMetrics(mTeamScore).height()) * 2);
    }

    int width()  const { return boundingRect().width();  }
    int height() const { return boundingRect().height(); }

    virtual void paint(QPainter* inPainter, const QStyleOptionGraphicsItem* /* Option */, QWidget* /* inWidget */)
    {
        int y = 0;
//        inPainter->drawRect(boundingRect());

        BOOST_FOREACH(const team& aTeam, mGame.teams)
        {
            int x = 0;
            inPainter->setFont(mTeamName);

            {
                QRectF rect(x, y, 125, QFontMetrics(mTeamName).height());
//                inPainter->drawRect(rect);
                inPainter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, QString::fromStdString(aTeam.team_name));
                x += rect.width();
            }

            inPainter->setFont(mTeamName);
            std::stringstream ss;
            if (aTeam.probable_pitcher)
            {
                ss << aTeam.probable_pitcher.get().winSummary();
            }
            else
            {
                ss << "TBD";
            }

            {
                QRectF rect(x, y, 200, QFontMetrics(mTeamName).height() + QFontMetrics(mTeamScore).height());
                //                inPainter->drawRect(rect);
                inPainter->setFont(QFont("lato", 16));
                inPainter->drawText(rect, Qt::AlignVCenter | Qt::AlignRight, QString::fromStdString(ss.str()));
            }

            y += QFontMetrics(mTeamName).height();

            {
                inPainter->setFont(mTeamScore);
                QRectF rect(0, y, 125, QFontMetrics(mTeamScore).height());
//                inPainter->drawRect(rect);
                inPainter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, QString::fromStdString(aTeam.record()));
            }

            y += QFontMetrics(mTeamScore).height();
        }
    }

protected:
    game mGame;
    QFont mTeamName;
    QFont mPitcher;
    QFont mTeamScore;
};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _PREVIEW_GRAPHICS_ITEM_HPP_ */
