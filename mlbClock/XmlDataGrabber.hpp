#ifndef _XML_DATA_GRABBER_HPP_
#define _XML_DATA_GRABBER_HPP_

#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <list>
#include <set>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <rapidxml>

#include <Language/Demangler.hpp>

namespace Citra { namespace mlbClock {

//static const char* DATA  = "data";
static const char* GAMES = "games";
static const char* GAME  = "game";

static const char* HOME = "home";
static const char* AWAY = "away";

//static const char* NAME_ABBREV  = "_name_abbrev";
//static const char* TEAM_NAME  = "_team_name";

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

struct mlbPlayer
{
    std::string first;
    std::string last;
    std::string name_display_roster;
    int         number;
    std::string pos;
};

struct mlbBatter : public mlbPlayer
{
    int   ab;
    float avg;
    int   h;
    int   hr;
    float obp;
    float ops;
    int   rbi;
    float slg;

    std::string Summary() const
    {
        std::stringstream ss;
        ss << name_display_roster << " (" << h << "-" << ab << ", " << avg << " AVG)";
        return ss.str();
    }
};

struct mlbPitcher : public mlbPlayer
{
    std::string era; // if a pitcher doesn't have an era they put in "-.--"
    int   losses;
    int   wins;
    int   saves;
    int   svo;

    std::string Summary() const
    {
        std::stringstream ss;
        ss << name_display_roster << " (" << era << ")";
        return ss.str();
    }

    std::string winSummary() const
    {
        std::stringstream ss;
        ss << name_display_roster << " (" << wins << "-" << losses << ", " << era << " ERA)";
        return ss.str();
    }

    std::string saveSummary() const
    {
        std::stringstream ss;
        ss << name_display_roster << " (" << saves << ")";
        return ss.str();
    }

};

struct team
{
    team() : TYPE(HOME), team_name(), name_abbrev(), innings(), runs(0), hits(0), errors(0) { }

    bool isNamed(const std::string& inTeamName) const
    {
        return (team_name == inTeamName || name_abbrev == inTeamName);
    }

    std::string record() const
    {
        std::stringstream ss;
        ss << wins << "-" << losses << std::endl;
        return ss.str();
    }

    std::string TYPE;
    std::string team_name;
    std::string name_abbrev;

    int wins;
    int losses;

    std::string time;
    std::string ampm;

    std::vector<int> innings;
    int runs;
    int hits;
    int errors;
    boost::optional<mlbPitcher> probable_pitcher;
};

struct game
{
    game() : teams(2), Day("DAY"), num(0), balls(0), strikes(0), outs(0), status()
    {
        away().TYPE = AWAY;
    }

    virtual ~game() { }

    bool containsTeam(const std::string& inTeamName) const
    {
        BOOST_FOREACH(const team& aTeam, teams)
        {
            if (aTeam.isNamed(inTeamName))
            {
                return true;
            }
        }
        return false;
    }

    std::string finalScore(const std::string& inTeam) const
    {
        const team& aTeam = (away().isNamed(inTeam) ? away() : home());
        const team& bTeam = (away().isNamed(inTeam) ? home() : away());

        std::stringstream ss;
        ss << (aTeam.runs > bTeam.runs ? "W " : "L ");
        ss << aTeam.runs << "-" << bTeam.runs;

        return ss.str();
    }

    std::string gameTime() const
    {
        return time + " " + ampm;
    }


    std::string teamTime(const std::string& inTeamName) const
    {
        BOOST_FOREACH(const team& aTeam, teams)
        {
            if (aTeam.isNamed(inTeamName))
            {
                return aTeam.time + " " + aTeam.ampm;
            }
        }

        throw;
    }

    std::string BSO() const
    {
        std::stringstream ss;
        ss << balls << "-" << strikes << " " << outs << " out";

        return ss.str();
    }

    bool isOver() const
    {
        return status == "Final" || status == "Game Over";
    }

    std::vector<team> teams;
    std::string Day;
    int num;

    int balls;
    int strikes;
    int outs;

    std::string status;

    std::string time;
    std::string time_zone;
    std::string ampm;

//    <batter ab="1" avg=".242" first="Nick" h="1" hr="6" id="608384" last="Williams" name_display_roster="Williams" number="5" obp=".311" ops=".736" pos="LF" rbi="14" slg=".425"/>
//    <pitcher er="1" era="3.18" first="Dereck" id="605446" ip="2.1" last="Rodriguez" losses="0" name_display_roster="Rodriguez" number="57" wins="0"/>

//    <pbp last="Cesar Hernandez singles on a line drive to left fielder Mac Williamson. "/>
//    <runners_on_base status="2">
//    <runner_on_1b first="Carlos" id="467793" last="Santana" name_display_roster="Santana" number="41"/>
//    <runner_on_2b first="Cesar" id="514917" last="Hernandez" name_display_roster="Hernandez" number="16"/>
//    </runners_on_base>
    boost::optional<int> inning;
    boost::optional<std::string> inning_state;

    bool runner_on_1b;
    bool runner_on_2b;
    bool runner_on_3b;

    boost::optional<mlbPitcher> pitcher;
    boost::optional<mlbBatter> batter;

    boost::optional<mlbPitcher> winning_pitcher;
    boost::optional<mlbPitcher> losing_pitcher;
    boost::optional<mlbPitcher> save_pitcher;

    team& away() { return teams[0]; }
    team& home() { return teams[1]; }

    const team& away() const { return teams[0]; }
    const team& home() const { return teams[1]; }
};

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

game buildGame(rapidxml::xml_node<>* inGameNode)
{
    game aGame;
//    aGame.num = inDay;

//    try
//    {
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
            BOOST_FOREACH(team& aTeam, aGame.teams)
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

//    }
//    catch(std::exception ex)
//    {
//        std::cerr << "ERROR making game " << ex.what() << std::endl;
//        throw ex;
//    }

    return aGame;
}

inline bool fileExists(const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

bool containsTeam(rapidxml::xml_node<>* aGameNode, const std::string& inTeam)
{
    return  aGameNode->first_attribute("home_team_name")->value()   == inTeam ||
            aGameNode->first_attribute("home_name_abbrev")->value() == inTeam ||
            aGameNode->first_attribute("away_team_name")->value()   == inTeam ||
            aGameNode->first_attribute("away_name_abbrev")->value() == inTeam;
}

class DataGrabber
{
    public:
        virtual ~DataGrabber() { }

        static std::string cacheData(int inYear, int inMonth, int inDay)
        {
            std::stringstream ss;
            ss << boost::format("gd2.mlb.com/components/game/mlb/year_%1%/month_%2%/day_%3%/master_scoreboard.xml")
                  % inYear
                  % boost::io::group(std::setfill('0'), std::setw(2), inMonth)
                  % boost::io::group(std::setfill('0'), std::setw(2), inDay);

            std::string aFileName = ss.str();

//            if (!fileExists(aFileName))
            {
                std::string aCmd = "wget -p -q http://";
                aCmd += aFileName;
                system(aCmd.c_str());
            }

            return aFileName;
        }

        static std::list<game> getGameList(int inYear, int inMonth, int inDay)
        {
            std::string aFileName = cacheData(inYear, inMonth, inDay);

            std::list<game> results;

            std::ifstream aFileStream(aFileName);
            std::vector<char> aFileBuffer((std::istreambuf_iterator<char>(aFileStream)), std::istreambuf_iterator<char>());
            aFileBuffer.push_back('\0');

            rapidxml::xml_document<> aXmlDocument;
            aXmlDocument.parse<0>(&aFileBuffer[0]);

            rapidxml::xml_node<>* aRootNode = aXmlDocument.first_node(GAMES);

            if (aRootNode)
            {
                for (rapidxml::xml_node<>* aGameNode = aRootNode->first_node(GAME); aGameNode; aGameNode = aGameNode->next_sibling())
                {
                    results.push_back(buildGame(aGameNode));
                    results.back().num = inDay;
                }
            }
            else
            {
                std::cerr << "FILE ERROR: '" << aFileName << "' missing root tag <" << GAMES << ">" << std::endl;
            }

            return results;
        }

        static std::list<game> getGameList(const boost::gregorian::date& inDate)
        {
            return getGameList(inDate.year(),
                               inDate.month(),
                               inDate.day());
        }

        static std::vector<game> getGames(const std::string& inTeam)
        {
            std::vector<game> outGames;

            boost::gregorian::date aDay = boost::gregorian::day_clock::local_day();
            aDay -= boost::gregorian::days(2);

            while (outGames.size() < 5)
            {
                std::list<game> aGameList = getGameList(aDay);

                BOOST_FOREACH(const game& aGame, aGameList)
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

    protected:
        DataGrabber() { }

};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _XML_DATA_GRABBER_HPP_ */
