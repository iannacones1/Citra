#ifndef _i_MLB_DATA_GRABBER_H_
#define _i_MLB_DATA_GRABBER_H_

#include <mlbClock/mlbData.hpp>

#include <list>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/foreach.hpp>

namespace Citra { namespace mlbClock { namespace Interfaces {

class iMlbDataGrabber
{
    public:
        iMlbDataGrabber() { }
        virtual ~iMlbDataGrabber() { }

        virtual std::list<mlbGame> getGameList(int inYear, int inMonth, int inDay) = 0;

        virtual std::list<mlbGame> getGameList(const boost::gregorian::date& inDate)
        {
            return getGameList(inDate.year(),
                               inDate.month(),
                               inDate.day());
        }

        std::vector<mlbGame> getGames(const std::string& inTeam)
        {
            std::vector<mlbGame> outGames;

            boost::gregorian::date aDay = boost::gregorian::day_clock::local_day();
            aDay -= boost::gregorian::days(2);

            while (outGames.size() < 5)
            {
                std::list<mlbGame> aGameList = this->getGameList(aDay);

                BOOST_FOREACH(const mlbGame& aGame, aGameList)
                {
                    if (aGame.containsTeam(inTeam))
                    {
                        outGames.push_back(aGame);
                    }
                }

                aDay += boost::gregorian::days(1);
            }

            return outGames;
        }

};

} /* namespace Interfaces*/ } /* namespace mlbClock */ } /* namespace Citra */

#endif /* _i_MLB_DATA_GRABBER_H_ */
