/*
 * This procedure sets up the variables for the translation of plotter
 * coordinates to PostScript coordinates.
 *
 * Don McCormick
 */
#include "defn.h"

static float psxmax, psymax ;		/* Sizes scaled to the viewport */
static float DefXScale, DefYScale ;	/* Default scales */

viewport(status)
int status ;
{
    float margin ;			/* Non printing area around paper */
    float pagewidth, pageheight ;	/* Maximum paper sizes */

    pagewidth = PAGEWIDTH ;
    pageheight = PAGEHEIGHT ;
    margin = PAGEMARGIN ;

    if (status == 1)			/* Set up initial conditions */
    {
	if (LANDSCAPE)		/* Create a positive Y axis */
	{
	    printf("90 rotate\n") ;
	    printf("0 -%g mm translate\n", pagewidth) ;
	    psymax = pagewidth - margin * 2 ;
	    psxmax = psymax * (maxXrange) / (maxYrange) ;
	    XOFFSET = xoffset + (pageheight - psxmax) / 2.0 ;
	    YOFFSET = yoffset + (margin) ;
	}
        else
        {
	    psxmax = pagewidth - margin * 2 ;
	    psymax = psxmax * (maxYrange) / (maxXrange) ;
	    XOFFSET = yoffset + (margin) ;
	    YOFFSET = yoffset + (pageheight - psymax) / 2.0 ;
        }
	printf("/%s %g Font\n", font, char_height) ;
	DefXScale = psxmax / (maxXrange) * SCALE ;
	DefYScale = psymax / (maxYrange) * SCALE ;
    }

    if (SCALING)
    {
        XSCALE = DefXScale * (P2x - P1x) / (U2x - U1x) ;
        YSCALE = DefYScale * (P2y - P1y) / (U2y - U1y) ;
    }
    else
    {
	XSCALE = DefXScale ;
	YSCALE = DefYScale ;
    }
    if (DEBUG)
    {
	fprintf(stderr,"Xscale= %g, Yscale = %g\n", XSCALE, YSCALE) ;
	fprintf(stderr,"Xoffset= %g, Yoffset = %g\n", XOFFSET, YOFFSET) ;
    }
}
