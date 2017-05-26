#include "defn.h"

linesize()
{
    int		ipen = 0;
    float	linewidth;

   if (SIGNED_NUMERIC)
	ipen = getval() - 1;

   if (ipen < 0 || ipen > 8)
	ipen = 0;

    linewidth = pen_size[ipen] * SCALE;		/* In mm */
    printf("%g mm setlinewidth\n", linewidth);
}
