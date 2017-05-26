#include "defn.h"

#define MAXDRAWPOINTS	1000

plotps(type)
char   *type;
{
    if (type == MOVE || type == RMOVE)
    {
	while (SIGNED_NUMERIC)
	{
	    if (type == MOVE)
	    {
		end_draw();
		absX = lastXmove = getval() * XSCALE + XOFFSET;
		absY = lastYmove = getval() * YSCALE + YOFFSET;
	    } else
	    if (type == RMOVE)
	    {
		end_draw();
		lastXmove = absX += getval() * XSCALE;
		lastYmove = absY += getval() * YSCALE;
	    }
	}
    }
    else			/* Must be a DRAW or RDRAW */
    {
	while (SIGNED_NUMERIC)
	{
	    if (dcount++ >= MAXDRAWPOINTS)
	    {
		end_draw();
		printf("newpath\n");
		printf("  %g %g %s\n", absX, absY, MOVE);
		DRAW_FLAG = 1;
		fprintf(stderr, "Warning exceeded %d draw points\n",
			MAXDRAWPOINTS);
	    }
	    xval = getval();		/* Get HPGL X value */
	    yval = getval();		/* Get HPGL Y value */
	    if (!DRAW_FLAG)
	    {
		printf("newpath\n");
		printf("  %g %g %s\n", absX, absY, MOVE);
		DRAW_FLAG = 1;
	    }
	    if (type == RDRAW)
	    {
		float rxval, ryval;

		rxval = xval * XSCALE;
		ryval = yval * YSCALE;
		absX += rxval;
		absY += ryval;
		printf("  %g %g %s\n", rxval, ryval, RDRAW);
	    } else
	    if (type == DRAW)
	    {
		absX = xval * XSCALE + XOFFSET;
		absY = yval * YSCALE + YOFFSET;
		printf("  %g %g %s\n", absX, absY, DRAW);
	    } else
	    {
		fprintf(stderr, "Error: expecting draw command not %s\n", type);
		exit(1);
	    }
	}
    }
}
