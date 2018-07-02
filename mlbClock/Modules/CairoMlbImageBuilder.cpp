
#include <mlbClock/Interfaces/iMlbImageBuilder.h>

#include <Module/create_module_macro.h>

#include <cairo.h>

#include <iostream>
#include <math.h>

#include <cstdio> // for stdout

namespace Citra { namespace mlbClock {

static const int W = 640;
static const int H = 384;

class CairoMlbImageBuilder : public Interfaces::iMlbImageBuilder
{
  public:
    CairoMlbImageBuilder() : Interfaces::iMlbImageBuilder() { }

    virtual ~CairoMlbImageBuilder() { }

    virtual Display::ImageBuffer buildImage(const std::string& inTeam, const std::vector<mlbGame>& inGameList)
    {
        std::cout << __func__ << " " << inTeam << std::endl;

        size_t focalGame = (inGameList.at(2).status == "Preview" ? 1 : 2);

        mlbGame cGame = inGameList.at(focalGame);

        cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, W, H);
        cairo_t* cr = cairo_create(surface);

        double xc = 128.0;
        double yc = 128.0;
        double radius = 100.0;
        double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
        double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */

        cairo_set_line_width (cr, 10.0);
        cairo_arc (cr, xc, yc, radius, angle1, angle2);
        cairo_stroke (cr);

        /* draw helping lines */
        cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
        cairo_set_line_width (cr, 6.0);

        cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
        cairo_fill (cr);

        cairo_arc (cr, xc, yc, radius, angle1, angle1);
        cairo_line_to (cr, xc, yc);
        cairo_arc (cr, xc, yc, radius, angle2, angle2);
        cairo_line_to (cr, xc, yc);
        cairo_stroke (cr);

        cairo_surface_write_to_png(surface, "test.png");

        // flush to ensure all writing to the image was done
        cairo_surface_flush (surface);

        // modify the image
        unsigned char* data = cairo_image_surface_get_data (surface);

        Citra::Display::ImageBuffer aImgBuf(W, H);

        for (size_t i = 0; i < H * W; i++)
        {
            aImgBuf.set(i, data[i]);
        }

        return aImgBuf;
    }

  protected:

};

MODULE(Interfaces::iMlbImageBuilder, CairoMlbImageBuilder)

} /* namespace mlbClock */ } /* namespace Citra */
