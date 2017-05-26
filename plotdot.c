/*
 * Plot a dot or symbol on the paper 
 *
 * This doesnot quite emulate what HPGL is suposed to do.
 *
 * A symbol should be placed at the end of each vector, however this will
 * only occur in the penup or non draw mode and not for pendown or the draw
 * mode. The main problem is due to my limited knowledge of the PostScript
 * language, it is not quite a simple matter of combining lineplot and
 * text drawing commands.
 *
 * Don McCormick
 */
#include "defn.h"

plotdot(type)
char   *type;
{
    end_draw();

    while (SIGNED_NUMERIC)
    {
	xval = getval();
	yval = getval();
	if (type == RMOVE)
	{
	    absX += xval * XSCALE;
	    absY += yval * YSCALE;
	} else
	if (type == MOVE)
	{
	    absX = xval * XSCALE + XOFFSET;
	    absY = yval * YSCALE + YOFFSET;
	} else
	{
	    fprintf(stderr, "Error: expecting move command not %s\n", type);
	    exit(1);
	}

	if (SYMBOL)
	    printf("%g %g 5 %g (%c) Text\n", absX, absY, char_angle, symbol);
    	else if (SETDOT)
	{
    	    printf("newpath\n");
    	    printf("  %g %g %s %g %g %s\n", absX, absY, MOVE, absX, absY, DRAW);
	    printf("stroke\n");
	}
    }
}
