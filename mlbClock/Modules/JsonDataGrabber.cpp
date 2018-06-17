#include "mlbDataNames.hpp"

#include <mlbClock/Interfaces/iMlbDataGrabber.h>
#include <Language/Exception.hpp>
#include <Language/Demangler.hpp>
#include <Module/create_module_macro.h>

#include <iostream>
#include <fstream>
#include <list>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include <jsoncpp/json/json.h>


namespace Citra { namespace mlbClock {

static const char* DATA        = "data";
static const char* TEAM_NAME   = "_team_name";
static const char* NAME_ABBREV = "_name_abbrev";

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

mlbGame buildGame(const Json::Value& inData)
{
    mlbGame aGame;

    try
    {
        const Json::Value& innings = inData[LINESCORE][INNING];

        BOOST_FOREACH(mlbTeam& aTeam, aGame.teams)
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
            BOOST_FOREACH(mlbTeam& aTeam, aGame.teams)
            {
                assignValue(aTeam.innings.at(i), innings[i][aTeam.TYPE]);
            }
        }

    }
    catch(...)
    {
//        std::cerr << "ERROR makeing mlbGame" << std::endl;
    }

    return aGame;
}

class JsonDataGrabber : public Interfaces::iMlbDataGrabber
{
    public:
        JsonDataGrabber() : Interfaces::iMlbDataGrabber() { }
        virtual ~JsonDataGrabber() { }

        static std::string cacheData(int inYear, int inMonth, int inDay)
        {
            std::stringstream ss;
            ss << boost::format("gd2.mlb.com/components/game/mlb/year_%1%/month_%2%/day_%3%/master_scoreboard.json")
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

            std::ifstream ifs(aFileName);
            Json::Reader reader;
            Json::Value obj;
            reader.parse(ifs, obj);

            Json::Value& games = obj[DATA][GAMES];

            std::list<mlbGame> results;

            for (size_t i = 0; i < games.size(); i++)
            {
                results.push_back(buildGame(games[GAME][i]));
            }

            return results;
        }
};

MODULE(Interfaces::iMlbDataGrabber, JsonDataGrabber)

} /* namespace mlbClock */ } /* namespace Citra */
