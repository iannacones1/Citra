#ifndef _XML_DATA_GRABBER_HPP_
#define _XML_DATA_GRABBER_HPP_

#include <Language/Exception.hpp>
#include <mlbClock/Interfaces/iMlbDataGrabber.h>
#include <Module/create_module_macro.h>

#include <fstream>
#include <iomanip>
#include <list>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <rapidxml>

namespace Citra { namespace mlbClock {

static const char* GAMES = "games";
static const char* GAME  = "game";

static const char* LINESCORE  = "linescore";
static const char* INNING     = "inning";

static const char* RUNS   = "r";
static const char* HITS   = "h";
static const char* ERRORS = "e";

static const char* DAY     = "day";
static const char* STATUS  = "status";

static const char* BALLS   = "balls";
static const char* STRIKES = "strikes";
static const char* OUTS    = "outs";

template <typename T>
void assignValue(std::vector<T>& outValue, const std::string& inValue)
{
    if (inValue.size())
    {
        outValue.push_back(boost::lexical_cast<T>(inValue));
    }
}

template <typename T>
void assignValue(T& outValue, const std::string& inValue)
{
    if (inValue.size())
    {
        outValue = boost::lexical_cast<T>(inValue);
    }
    else
    {
        outValue = T();
    }
}

template <typename T>
void assignValue(T& outValue, const rapidxml::xml_node<>* inNode)
{
    assignValue(outValue, inNode->value());
}

template <typename T>
bool assignValue(T& outValue, const rapidxml::xml_attribute<>* inAttr)
{
    if (inAttr)
    {
        std::string aVal = inAttr->value();
        if (aVal.size())
        {
            outValue = boost::lexical_cast<T>(aVal);
            return true;
        }
    }

    return false;
}

template <typename T>
void assignValue(std::vector<T>& outValue, const rapidxml::xml_attribute<>* inAttr)
{
    T result;
    if (assignValue(result, inAttr))
    {
        outValue.push_back(result);
    }
}

template <typename T>
bool assignValue(boost::optional<T>& outValue, const rapidxml::xml_attribute<>* inAttr)
{
    if (inAttr)
    {
        std::string aVal = inAttr->value();
        if (aVal.size())
        {
            T newVal = boost::lexical_cast<T>(aVal);
            outValue = boost::optional<T>(newVal);
            return true;
        }
    }

    return false;
}

bool updatePlayer(mlbPlayer& outPlayer, rapidxml::xml_node<>* inNode)
{
    bool valid = true;
    valid &= assignValue(outPlayer.first,               inNode->first_attribute("first"              ));
    valid &= assignValue(outPlayer.last,                inNode->first_attribute("last"               ));
    valid &= assignValue(outPlayer.number,              inNode->first_attribute("number"             ));
    valid &= assignValue(outPlayer.name_display_roster, inNode->first_attribute("name_display_roster"));
             assignValue(outPlayer.pos,                 inNode->first_attribute("pos"                ));

    return valid;
}

boost::optional<mlbPitcher> buildPitcher(rapidxml::xml_node<>* inNode)
{
    if (inNode)
    {
        mlbPitcher aPitcher;
        bool valid = updatePlayer(aPitcher, inNode);
        valid &= assignValue(aPitcher.era,    inNode->first_attribute("era"   ));
        valid &= assignValue(aPitcher.losses, inNode->first_attribute("losses"));
        valid &= assignValue(aPitcher.wins,   inNode->first_attribute("wins"  ));
                 assignValue(aPitcher.saves,  inNode->first_attribute("saves" ));
                 assignValue(aPitcher.svo,    inNode->first_attribute("svo"   ));

        if (valid)
        {
            return boost::optional<mlbPitcher>(aPitcher);
        }
    }

    return boost::optional<mlbPitcher>();
}

boost::optional<mlbBatter> buildBatter(rapidxml::xml_node<>* inNode)
{
    if (inNode)
    {
        mlbBatter aBatter;
        bool valid = updatePlayer(aBatter, inNode);
        valid &= assignValue(aBatter.ab,  inNode->first_attribute("ab" ));
        valid &= assignValue(aBatter.avg, inNode->first_attribute("avg"));
        valid &= assignValue(aBatter.h,   inNode->first_attribute("h"  ));
        valid &= assignValue(aBatter.hr,  inNode->first_attribute("hr" ));
        valid &= assignValue(aBatter.obp, inNode->first_attribute("obp"));
        valid &= assignValue(aBatter.ops, inNode->first_attribute("ops"));
        valid &= assignValue(aBatter.rbi, inNode->first_attribute("rbi"));
        valid &= assignValue(aBatter.slg, inNode->first_attribute("slg"));

        if (valid)
        {
            return boost::optional<mlbBatter>(aBatter);
        }
    }

    return boost::optional<mlbBatter>();
}

mlbGame buildGame(rapidxml::xml_node<>* inGameNode)
{
    mlbGame aGame;
        assignValue(aGame.Day,       inGameNode->first_attribute(DAY));
        assignValue(aGame.time,      inGameNode->first_attribute("time"));
        assignValue(aGame.time_zone, inGameNode->first_attribute("time_zone"));
        assignValue(aGame.ampm,      inGameNode->first_attribute("ampm"));

        assignValue(aGame.home().team_name,   inGameNode->first_attribute("home_team_name"));
        assignValue(aGame.home().name_abbrev, inGameNode->first_attribute("home_name_abbrev"));

        assignValue(aGame.away().team_name,   inGameNode->first_attribute("away_team_name"));
        assignValue(aGame.away().name_abbrev, inGameNode->first_attribute("away_name_abbrev"));

        assignValue(aGame.home().wins,   inGameNode->first_attribute("home_win"));
        assignValue(aGame.home().losses, inGameNode->first_attribute("home_loss"));

        assignValue(aGame.away().wins,   inGameNode->first_attribute("away_win"));
        assignValue(aGame.away().losses, inGameNode->first_attribute("away_loss"));

        assignValue(aGame.home().time, inGameNode->first_attribute("time_hm_lg"));
        assignValue(aGame.home().ampm, inGameNode->first_attribute("home_ampm"));

        assignValue(aGame.away().time, inGameNode->first_attribute("time_aw_lg"));
        assignValue(aGame.away().ampm, inGameNode->first_attribute("away_ampm"));

        rapidxml::xml_node<>* aPBPNode = inGameNode->first_node("pbp");
        if (aPBPNode)
        {
            assignValue(aGame.pbp, aPBPNode->first_attribute("last"));
        }

        rapidxml::xml_node<>* aStatusNode = inGameNode->first_node(STATUS);

        assignValue(aGame.status, aStatusNode->first_attribute(STATUS));

        if (!assignValue(aGame.balls, aStatusNode->first_attribute(BALLS)))
        {
            assignValue(aGame.balls, aStatusNode->first_attribute("b"));
        }

        if (!assignValue(aGame.strikes, aStatusNode->first_attribute(STRIKES)))
        {
            assignValue(aGame.strikes, aStatusNode->first_attribute("s"));
        }

        if (!assignValue(aGame.outs, aStatusNode->first_attribute(OUTS)))
        {
            assignValue(aGame.outs, aStatusNode->first_attribute("o"));
        }

        assignValue(aGame.inning,       aStatusNode->first_attribute("inning"));
        assignValue(aGame.inning_state, aStatusNode->first_attribute("inning_state"));

        rapidxml::xml_node<>* aLinescoreNode = inGameNode->first_node(LINESCORE);

        if (aLinescoreNode)
        {
            BOOST_FOREACH(mlbTeam& aTeam, aGame.teams)
            {
                assignValue(aTeam.runs,   aLinescoreNode->first_node(RUNS)->first_attribute(aTeam.TYPE.c_str()));
                assignValue(aTeam.hits,   aLinescoreNode->first_node(HITS)->first_attribute(aTeam.TYPE.c_str()));
                assignValue(aTeam.errors, aLinescoreNode->first_node(ERRORS)->first_attribute(aTeam.TYPE.c_str()));

                for (rapidxml::xml_node<>* aInningNode = aLinescoreNode->first_node(INNING); aInningNode; aInningNode = aInningNode->next_sibling(INNING))
                {
                    assignValue(aTeam.innings, aInningNode->first_attribute(aTeam.TYPE.c_str()));
                }
            }
        }

        aGame.home().probable_pitcher = buildPitcher(inGameNode->first_node("home_probable_pitcher"));
        aGame.away().probable_pitcher = buildPitcher(inGameNode->first_node("away_probable_pitcher"));

        aGame.winning_pitcher = buildPitcher(inGameNode->first_node("winning_pitcher"));
        aGame.losing_pitcher  = buildPitcher(inGameNode->first_node("losing_pitcher"));
        aGame.save_pitcher    = buildPitcher(inGameNode->first_node("save_pitcher"));

        aGame.pitcher = buildPitcher(inGameNode->first_node("pitcher"));
        aGame.batter  = buildBatter(inGameNode->first_node("batter"));

        rapidxml::xml_node<>* aRunnersOnBaseNode = inGameNode->first_node("runners_on_base");

        aGame.runner_on_1b = (aRunnersOnBaseNode && aRunnersOnBaseNode->first_node("runner_on_1b"));
        aGame.runner_on_2b = (aRunnersOnBaseNode && aRunnersOnBaseNode->first_node("runner_on_2b"));
        aGame.runner_on_3b = (aRunnersOnBaseNode && aRunnersOnBaseNode->first_node("runner_on_3b"));

    return aGame;
}

class XmlDataGrabber : public Interfaces::iMlbDataGrabber
{
    public:
        XmlDataGrabber() : Interfaces::iMlbDataGrabber() { }
        virtual ~XmlDataGrabber() { }

        static std::string cacheData(int inYear, int inMonth, int inDay)
        {
            std::stringstream ss;
            ss << boost::format("gd2.mlb.com/components/game/mlb/year_%1%/month_%2%/day_%3%/master_scoreboard.xml")
                  % inYear
                  % boost::io::group(std::setfill('0'), std::setw(2), inMonth)
                  % boost::io::group(std::setfill('0'), std::setw(2), inDay);

            std::string aFileName = ss.str();

            { // TODO: replace with non system call
                std::string aCmd = "wget -p -q http://";
                aCmd += aFileName;
                system(aCmd.c_str());
            }

            return aFileName;
        }

        virtual std::list<mlbGame> getGameList(int inYear, int inMonth, int inDay)
        {
            std::string aFileName = cacheData(inYear, inMonth, inDay);

            std::ifstream aFileStream(aFileName);
            std::vector<char> aFileBuffer((std::istreambuf_iterator<char>(aFileStream)), std::istreambuf_iterator<char>());
            aFileBuffer.push_back('\0');

            rapidxml::xml_document<> aXmlDocument;
            aXmlDocument.parse<0>(&aFileBuffer[0]);

            rapidxml::xml_node<>* aRootNode = aXmlDocument.first_node(GAMES);

            if (!aRootNode)
            {
                std::stringstream ss; ss << "FILE ERROR: '" << aFileName << "' missing root tag <" << GAMES << ">";
                throw Language::Exception(ss);
            }

            std::list<mlbGame> results;

            for (rapidxml::xml_node<>* aGameNode = aRootNode->first_node(GAME); aGameNode; aGameNode = aGameNode->next_sibling())
            {
                results.push_back(buildGame(aGameNode));
                results.back().num = inDay;
            }

            return results;
        }
};


MODULE(Interfaces::iMlbDataGrabber, XmlDataGrabber)

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _XML_DATA_GRABBER_HPP_ */
