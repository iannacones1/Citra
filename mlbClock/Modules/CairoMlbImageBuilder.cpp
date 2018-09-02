
#include <mlbClock/Interfaces/iMlbImageBuilder.h>

#include <Module/create_module_macro.h>

#include <cairo.h>

#include <math.h>

#include <iomanip>      // std::setw
#include <iostream> // std::cout, std::endl;
#include <cstdio> // for stdout

namespace Citra { namespace mlbClock {

static const int W = 640;
static const int H = 384;

static const int BOX_WIDTH  = W/5;
static const int BOX_HEIGHT = BOX_WIDTH * 0.75;

static const int SPACEING    = 30;
static const int FONT_HEIGHT = 23;

class CairoMlbImageBuilder : public Interfaces::iMlbImageBuilder
{
  public:
    CairoMlbImageBuilder() : Interfaces::iMlbImageBuilder() { }

    virtual ~CairoMlbImageBuilder() { }

    void centerText(cairo_t* inCairo, int inX, int inY, const std::string& inText)
    {
        cairo_text_extents_t extents;
        cairo_text_extents(inCairo, inText.c_str(), &extents);

        cairo_move_to(inCairo, inX - extents.width/2, inY + extents.height/2);
        cairo_show_text(inCairo, inText.c_str());
    }

    template<typename T>
    void centerText(cairo_t* inCairo, int inX, int inY, const T& inValue)
    {
        std::stringstream ss;
        ss << inValue;
        centerText(inCairo, inX, inY, ss.str());
    }

    void addDaySummary(cairo_t* inCairo, int X, int Y, const mlbGame& inGame, const std::string& inTeam, bool inFocal)
    {
        std::cout << "X=" << X << " Y=" << Y << " " << inTeam << " " << inFocal << std::endl;

        cairo_rectangle(inCairo, X, Y, BOX_WIDTH, (inFocal ? 0 : BOX_HEIGHT));

        cairo_set_font_size(inCairo, 14);

        { // DAY (Top Left)
            cairo_text_extents_t extents;
            cairo_text_extents(inCairo, inGame.Day.c_str(), &extents);

            cairo_move_to(inCairo, X + 5, Y + extents.height + 5);
            cairo_show_text(inCairo, inGame.Day.c_str());
        }

        { // NUM (Top Right)
            std::stringstream ss; ss << inGame.num;

            cairo_text_extents_t extents;
            cairo_text_extents(inCairo, ss.str().c_str(), &extents);

            cairo_move_to(inCairo, X + BOX_WIDTH - 5 - extents.width, Y + extents.height + 5);
            cairo_show_text(inCairo, ss.str().c_str());
        }

        { // Score / Time (Bottom Middle)
            std::string aText = inGame.teamTime(inTeam);

            if (inGame.status == "Final")
            {
                aText = inGame.finalScore(inTeam);
            }
            else if (inGame.status == "In Progress")
            {
                aText = "LIVE";
            }

            cairo_text_extents_t extents;
            cairo_text_extents(inCairo, aText.c_str(), &extents);

            cairo_move_to(inCairo, X + BOX_WIDTH/2 - extents.width/2, Y + BOX_HEIGHT - 5);
            cairo_show_text(inCairo, aText.c_str());
        }

        { // Team Name (Center)
            cairo_set_font_size(inCairo, 26);

            std::string aText = (inGame.home().isNamed(inTeam) ? inGame.away().name_abbrev : "@" + inGame.home().name_abbrev);

            centerText(inCairo, X + BOX_WIDTH/2, Y + BOX_HEIGHT/2, aText);
        }
    }

    void addLinescore(cairo_t* inCairo, const mlbGame& inGame)
    {
        int X = W/2;
        int Y = H/2;

        size_t aInningCount = std::max(inGame.away().innings.size(), (size_t)9);

        {
            float w = SPACEING * 1.5;     // Team names
            w += SPACEING * aInningCount; // inning scores
            w += SPACEING * 3.25;         // R H E
            if (!inGame.isOver()) { w += FONT_HEIGHT * 3; } // Basescores

            X -= w/2; // Center X
        }

        int x = X + SPACEING * 1.5;
        int y = Y;

        cairo_set_font_size(inCairo, 14);

        for (size_t i = 0; i < aInningCount; i++)
        {
            std::stringstream ss; ss << i+1;

            centerText(inCairo, x, y, ss.str());

            x += SPACEING;
        }

        x += SPACEING/4;

        centerText(inCairo, x, y, "R"); x += SPACEING;
        centerText(inCairo, x, y, "H"); x += SPACEING;
        centerText(inCairo, x, y, "E"); x += SPACEING;

        // draw "box"
//        if (inGame.inning && inGame.inning_state && (inGame.inning_state.get() == "Top" || inGame.inning_state.get() == "Bottom"))
//        {
//            int yLoc = (inGame.inning_state.get() == "Top" ? y : y + FONT_HEIGHT);
//            QRectF rect(SPACEING * 1.5 + (SPACEING * (inGame.inning.get() - 1)), yLoc, SPACEING, FONT_HEIGHT);
//            inPainter->drawRect(rect);
//        }

        y += FONT_HEIGHT;

        BOOST_FOREACH(const mlbTeam& aTeam, inGame.teams)
        {
            x = X;

            { // Team Name (This should be bold?)
                cairo_text_extents_t extents;
                cairo_text_extents(inCairo, aTeam.name_abbrev.c_str(), &extents);

                cairo_move_to(inCairo, x, y + extents.height/2);
                cairo_show_text(inCairo, aTeam.name_abbrev.c_str());
            }

            x += SPACEING * 1.5;

            for (size_t i = 0; i < aInningCount; i++)
            {
                if (i < aTeam.innings.size())
                {
                    centerText(inCairo, x, y, aTeam.innings.at(i));
                }
                else if (inGame.isOver())
                {
                    centerText(inCairo, x, y, "X");
                }

                x += SPACEING;
            }

            x += SPACEING/4;

            centerText(inCairo, x, y, aTeam.runs);   x += SPACEING;
            centerText(inCairo, x, y, aTeam.hits);   x += SPACEING;
            centerText(inCairo, x, y, aTeam.errors); x += SPACEING;

            y += FONT_HEIGHT;
        }

    }

    unsigned char mask(unsigned char* inColor)
    {
        int alpha = inColor[0];
//        int color = inColor[1] + inColor[2] + inColor[3];

        // half of 255 cause everthing is showing up in alpha
        int breakVal = 255 / 2;

        return (alpha < breakVal ? 0x00 : 0xFF);
    }

    virtual Display::ImageBuffer buildImage(const std::string& inTeam, const std::vector<mlbGame>& inGameList)
    {
        std::cout << __func__ << " " << inTeam << std::endl;

        size_t focalGame = (inGameList.at(2).status == "Preview" ? 1 : 2);

        mlbGame cGame = inGameList.at(focalGame);

        cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, W, H);

        cairo_t* aCairo = cairo_create(surface);

        cairo_select_font_face(aCairo, "lato", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

        for (size_t i = 0; i < inGameList.size(); i++)
        {
            int offset = (i > focalGame ? 1 : 0);
            addDaySummary(aCairo, (W/5) * i - offset, 0, inGameList.at(i), inTeam, i == focalGame);
        }

        // Game in progress
        addLinescore(aCairo, cGame);

        cairo_stroke(aCairo); // Drawls all the lines?

        cairo_surface_flush(surface); // flush to ensure all writing to the image was done

        cairo_surface_write_to_png(surface, "test.png");
        unsigned char* data = cairo_image_surface_get_data(surface);

        Citra::Display::ImageBuffer aImgBuf(W, H);

        for (size_t i = 0; i < H * W; i++)
        {
            aImgBuf.set(i, mask(&data[i*4]));
        }

        cairo_surface_destroy(surface);

        return aImgBuf;
    }

  protected:

};

MODULE(Interfaces::iMlbImageBuilder, CairoMlbImageBuilder)

} /* namespace mlbClock */ } /* namespace Citra */
