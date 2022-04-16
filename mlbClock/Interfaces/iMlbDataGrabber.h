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
        virtual ~iMlbDataGrabber() { }

        virtual std::list<mlbGame> getGameList(int inYear, int inMonth, int inDay) = 0;

        virtual std::list<mlbGame> getGameList(const boost::gregorian::date& inDate)
        {
            return getGameList(inDate.year(),
                               inDate.month(),
                               inDate.day());
        }

        void getGamesBefore(const boost::gregorian::date& inDay,
                            const std::string& inTeam,
                            std::list<mlbGame>& ioGames)
        {
            std::list<mlbGame> aGameList = this->getGameList(inDay);
            std::reverse(aGameList.begin(), aGameList.end());

            for (const mlbGame& aGame : aGameList)
            {
                if (aGame.containsTeam(inTeam))
                {
                    ioGames.push_front(aGame);
                }
            }

        }

        void getGamesAfter(const boost::gregorian::date& inDay,
                            const std::string& inTeam,
                            std::list<mlbGame>& ioGames)
        {
            std::list<mlbGame> aGameList = this->getGameList(inDay);

            for (const mlbGame& aGame : aGameList)
            {
                if (aGame.containsTeam(inTeam))
                {
                    ioGames.push_back(aGame);
                }
            }

        }

        std::vector<mlbGame> getGames(const std::string& inTeam)
        {
            std::list<mlbGame> aGameList;

            boost::gregorian::date aDay = boost::gregorian::day_clock::local_day();
            boost::gregorian::date bDay = aDay;
            aDay += boost::gregorian::days(2);

            while (aGameList.size() < 5)
            {
                getGamesBefore(bDay, inTeam, aGameList);
                bDay -= boost::gregorian::days(1);
            }
/*
            while (aGameList.size() > 2)
            {
                aGameList.pop_front();
            }

            while (aGameList.size() < 5)
            {
                getGamesAfter(aDay, inTeam, aGameList);
                aDay += boost::gregorian::days(1);
            }
*/

            while (aGameList.size() > 5)
            {
                aGameList.pop_back();
            }

            std::vector<mlbGame> outGames{ std::make_move_iterator(std::begin(aGameList)),
                                           std::make_move_iterator(std::end(aGameList)) };

            return outGames;
        }
    protected:
        iMlbDataGrabber() { }
};

} /* namespace Interfaces*/ } /* namespace mlbClock */ } /* namespace Citra */

#endif /* _i_MLB_DATA_GRABBER_H_ */
