/*
 * The input window provides a means of restricting the plotting outside
 * the specific rectangular area defined.
 * Used with the "IW" command (HPGL).
 *
 * NOTE There is no checking if the HPGL code is correct.
 */

#include "defn.h"

window()
{
    float XloLeft, YloLeft;
    float XupRight, YupRight;

    if (SIGNED_NUMERIC)
	XloLeft = getval() * XSCALE + XOFFSET;
    else
    {
	printf("newpath\n");
	printf("    0 0 moveto\n");
	printf("    300 mm 0 lineto\n");
	printf("    300 mm 210 mm lineto\n");
	printf("    0 210 mm lineto\n");
	printf("closepath clip\n");
	return;
    }

    if (SIGNED_NUMERIC)
	YloLeft = getval() * YSCALE + YOFFSET;
    if (SIGNED_NUMERIC)
	XupRight = getval() * XSCALE + XOFFSET;
    if (SIGNED_NUMERIC)
	YupRight = getval() * YSCALE + YOFFSET;

    printf("newpath\n");
    printf("    %g %g %s\n", XloLeft, YloLeft, MOVE);
    printf("    %g %g %s\n", XupRight, YloLeft, DRAW);
    printf("    %g %g %s\n", XupRight, YupRight, DRAW);
    printf("    %g %g %s\n", XloLeft, YupRight, DRAW);
    printf("closepath clip\n");
}
