#ifndef _DATA_GRABBER_HPP_
#define _DATA_GRABBER_HPP_

#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <list>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <jsoncpp/json/json.h>

#include <Language/Demangler.hpp>

namespace Citra { namespace mlbClock {

void PrintJSONValue( const Json::Value &val )
{
    if( val.isString() ) {
        printf( "string(%s)", val.asString().c_str() );
    } else if( val.isBool() ) {
        printf( "bool(%d)", val.asBool() );
    } else if( val.isInt() ) {
        printf( "int(%d)", val.asInt() );
    } else if( val.isUInt() ) {
        printf( "uint(%u)", val.asUInt() );
    } else if( val.isDouble() ) {
        printf( "double(%f)", val.asDouble() );
    }
    else
    {
        printf( "unknown type=[%d]", val.type() );
    }
}

bool PrintJSONTree( const Json::Value &root, unsigned short depth /* = 0 */)
{
    depth += 1;
    printf( " {type=[%d], size=%d}", root.type(), root.size() );

    if( root.size() > 0 ) {
        printf("\n");
        for( Json::Value::const_iterator itr = root.begin() ; itr != root.end() ; itr++ ) {
            // Print depth.
            for( int tab = 0 ; tab < depth; tab++) {
               printf("-");
            }
            printf(" subvalue(");
            PrintJSONValue(itr.key());
            printf(") -");
            PrintJSONTree( *itr, depth);
        }
        return true;
    } else {
        printf(" ");
        PrintJSONValue(root);
        printf( "\n" );
    }
    return true;
}

static const std::string DATA  = "data";
static const std::string GAMES = "games";
static const std::string GAME  = "game";

static const std::string HOME = "home";
static const std::string AWAY = "away";

static const std::string NAME_ABBREV  = "_name_abbrev";
static const std::string TEAM_NAME  = "_team_name";

static const std::string LINESCORE  = "linescore";
static const std::string INNING     = "inning";

static const std::string RUNS   = "r";
static const std::string HITS   = "h";
static const std::string ERRORS = "e";

struct team
{
    team() : TYPE(HOME) { }

    bool isNamed(const std::string& inTeamName) const
    {
        return (team_name == inTeamName || name_abbrev == inTeamName);
    }

    std::string TYPE;
    std::string team_name;
    std::string name_abbrev;
    std::vector<std::string> innings;
    int runs;
    int hits;
    int errors;

};

struct game
{
    game() : teams(2)
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

    std::vector<team> teams;
    team& away() { return teams[0]; }
    team& home() { return teams[1]; }

    const team& away() const { return teams[0]; }
    const team& home() const { return teams[1]; }
};

#define ASSIGN_CASE(type, getter) \
case type:     \
{              \
    try        \
    {          \
        outValue = boost::lexical_cast<T>(inValue.as##getter()); \
    }          \
    catch(...) \
    {          \
        std::cerr << "failed to cast Value:\'" << inValue.as##getter() << "\' as " << Language::Demangler::demangle(outValue) << std::endl; \
        throw; \
    }          \
    break;     \
}

template <typename T>
void assignValue(T& outValue, const Json::Value& inValue)
{
    switch (inValue.type())
    {
        case Json::nullValue:
        {
            outValue = T();
        }
        ASSIGN_CASE(Json::intValue,     Int   )
        ASSIGN_CASE(Json::uintValue,    UInt  )
        ASSIGN_CASE(Json::realValue,    Double)
        case Json::stringValue:
        {
            if (inValue.asString().empty())
            {
                outValue = T();
            }
            else
            {
                outValue = boost::lexical_cast<T>(inValue.asString());
            }
            break;
        }
        ASSIGN_CASE(Json::booleanValue, Bool  )
        case Json::arrayValue:
        {
            std::cerr << "What do?!?! Json::arrayValue" << std::endl;
            throw;
        }
        case Json::objectValue:
        {
            std::cerr << "What do?!?! Json::objectValue" << std::endl;
            throw;
        }
        default:
        {
            std::cerr << "unable to assing value" << std::endl;
            throw;
        }
    }
}

game buildGame(const Json::Value& inData)
{
    game aGame;

    try
    {
        const Json::Value& innings = inData[LINESCORE][INNING];

        BOOST_FOREACH(team& aTeam, aGame.teams)
        {
            assignValue(aTeam.team_name,   inData[aTeam.TYPE + TEAM_NAME  ]);
            assignValue(aTeam.name_abbrev, inData[aTeam.TYPE + NAME_ABBREV]);
            assignValue(aTeam.runs,        inData[LINESCORE][RUNS  ][aTeam.TYPE]);
            assignValue(aTeam.hits,        inData[LINESCORE][HITS  ][aTeam.TYPE]);
            assignValue(aTeam.errors,      inData[LINESCORE][ERRORS][aTeam.TYPE]);

            aTeam.innings.resize(innings.size());
        }

        for (size_t i = 0; i < innings.size(); i++)
        {
            BOOST_FOREACH(team& aTeam, aGame.teams)
            {
                assignValue(aTeam.innings.at(i), innings[i][aTeam.TYPE]);
            }
        }

    }
    catch(...)
    {
//        std::cerr << "ERROR makeing game" << std::endl;
    }

    return aGame;
}

inline bool fileExists(const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

class DataGrabber
{
    public:
        virtual ~DataGrabber() { }

        static game getGame(const std::string& inTeam, int inIndex)
        {
            int dir = (inIndex < 0 ? -1 : 1);
            int index = 0;

            int found = (inIndex < 0 ? -1 : 0);

            int secPerDay = (24 * 60 * 60);

            while (true)
            {
                std::string aFileName;

                { // TODO: Replace this with a call to libCurl
                    time_t rawtime;
                    struct tm* timeinfo;
                    char buffer [200];

                    time(&rawtime);

                    rawtime += (index * secPerDay);
                    index += dir;

                    timeinfo = localtime(&rawtime);

                    strftime(buffer,200,"gd2.mlb.com/components/game/mlb/year_%Y/month_%m/day_%d/master_scoreboard.json",timeinfo);

                    aFileName = std::string(buffer);

                    if (!fileExists(aFileName))
                    {
                        std::string aCmd = "wget -p -q http://";
                        aCmd += aFileName;

                        system(aCmd.c_str());
                    }
                }

                Json::Reader reader;
                std::ifstream ifs(aFileName);
                Json::Value obj;
                reader.parse(ifs, obj);

                Json::Value& games = obj[DATA][GAMES];

                for (size_t i = 0; i < games.size(); i++)
                {
                    game aGame = buildGame(games[GAME][i]);

                    if (aGame.containsTeam(inTeam))
                    {
                        if (found == inIndex)
                        {
                            return aGame;
                        }

                        found += dir;
                    }
                }

            }

            return game();
        }

    protected:
        DataGrabber() { }

};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _GPIO_HPP_ */
