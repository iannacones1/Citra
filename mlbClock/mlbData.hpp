#ifndef _MLB_DATA_HPP
#define _MLB_DATA_HPP

#include <string>
#include <vector>
#include <sstream>

#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace Citra { namespace mlbClock {

static const char* HOME = "home";
static const char* AWAY = "away";

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

struct mlbTeam
{
    mlbTeam() : TYPE(HOME), team_name(), name_abbrev(), innings(), runs(0), hits(0), errors(0) { }

    bool isNamed(const std::string& inTeamName) const
    {
        return (team_name == inTeamName || name_abbrev == inTeamName);
    }

    std::string record() const
    {
        std::stringstream ss;
        ss << wins << "-" << losses;
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

struct mlbGame
{
    mlbGame() : teams(2), Day("DAY"), num(0), balls(0), strikes(0), outs(0), status()
    {
        away().TYPE = AWAY;
    }

    virtual ~mlbGame() { }

    bool containsTeam(const std::string& inTeamName) const
    {
        BOOST_FOREACH(const mlbTeam& aTeam, teams)
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
        const mlbTeam& aTeam = (away().isNamed(inTeam) ? away() : home());
        const mlbTeam& bTeam = (away().isNamed(inTeam) ? home() : away());

        std::stringstream ss;

        ss << (aTeam.runs == bTeam.runs ? "T " : (aTeam.runs > bTeam.runs ? "W " : "L "));
        ss << aTeam.runs << "-" << bTeam.runs;

        return ss.str();
    }

    std::string gameTime() const
    {
        return time + " " + ampm;
    }

    std::string teamTime(const std::string& inTeamName) const
    {
        BOOST_FOREACH(const mlbTeam& aTeam, teams)
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
        return boost::starts_with(status, "Final") ||
               boost::starts_with(status, "Completed") ||
               status == "Game Over";
    }

    bool inProgress() const
    {
        return status == "In Progress" ||
               status == "Delay";
    }

    bool isUpdating() const
    {
        return inProgress();// ||
               //status == "Pre-Game";
    }

    std::vector<mlbTeam> teams;
    std::string Day;
    std::string time_date;
    int num;

    int balls;
    int strikes;
    int outs;

    std::string status;

    std::string time;
    std::string time_zone;
    std::string ampm;

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

    boost::optional<std::string> pbp;

    mlbTeam& away() { return teams[0]; }
    mlbTeam& home() { return teams[1]; }

    const mlbTeam& away() const { return teams[0]; }
    const mlbTeam& home() const { return teams[1]; }
};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _MLB_DATA_HPP */
