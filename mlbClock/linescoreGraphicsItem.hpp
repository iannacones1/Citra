#include <QtGui/QtGui>

static const int W = 640;
static const int H = 384;
static const int space = 40;

namespace Citra { namespace mlbClock {

class linescoreGraphicsItem : public QGraphicsItem
{
	linescoreGraphicsItem()
	{
		int x = 150;
		int y = 150 + space;
		int h = 23;

		for (size_t i = 0; i < aGame.away().innings.size(); i++)
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

			BOOST_FOREACH(const std::string& aRun, aTeam.innings)
			{
				addText(x, y, aRun, scene);
			}

			y += (space/4);

			addText(x, y, QString::number(aTeam.runs), scene);
			addText(x, y, QString::number(aTeam.hits), scene);
			addText(x, y, QString::number(aTeam.errors), scene);

			x += h;
		}
		std::cout << std::endl;
	}
	virtual ~linescoreGraphicsItem() { }

	void addText(int& x, int& y, const QString& inText, QGraphicsScene* scene)
	{
		QGraphicsTextItem* textItem = new QGraphicsTextItem(inText);
		textItem->setPos(y, x);
		scene->addItem(textItem);
		y += space/2;

		textItem->moveBy(-textItem->boundingRect().width()/2, 0);
	}

	void addText(int& x, int& y, const std::string& inText, QGraphicsScene* scene)
	{
		addText(x, y, QString::fromStdString(inText), scene);
	}
}

} /* namespace mlbClock */ } /* namespace Citra */
