#include "defn.h"

plotinit()
{
    /*
     * Initialisation of PostScript plot macros 
     */
    MOVE = "M";
    RMOVE = "R";
    DRAW = "D";
    RDRAW = "I";

    LANDSCAPE = TRUE;		/* Display plot in Landscape mode */

    PLOTABS = TRUE;		/* Absolute plot coordinates */

    PENDOWN = FALSE;		/* Penup */

    SETDOT = FALSE;		/* HP-GL only for linetype = 0 */

    SCALE = 1;	 		/* Default Scale, ie 1:1 */

    SYMBOL = 0;			/* HP-GL only */
    /*
     *	   Default line/pen sizes (in mm)
     */
    pen_size[0] = 0.1;
    pen_size[1] = 0.2;
    pen_size[2] = 0.3;
    pen_size[3] = 0.4;
    pen_size[4] = 0.5;
    pen_size[5] = 0.7;
    pen_size[6] = 1.0;
    pen_size[7] = 1.25;
    pen_size[8] = 1.5;

    font = "Courier";		/* Default font (mono spaced) */

    EOL = '\003';		/* End of line terminator default */

    /*
     * Default character specifications for plotter A4 paper
     */
    char_angle = 0;		/* Degrees */
    char_slant = 0;		/* tan(angle) */
    char_height = 2.7;		/* mm */
    char_space = 0.8;		/* mm */
    char_width = 1.9;		/* mm */
    /*
     * Page offsets set to zero
     */
    xoffset = yoffset = 0;
    /*
     * Define degree to radian parameter
     */
    deg2rad = asin(1.0) / 90.0;
}
