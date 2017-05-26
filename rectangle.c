#include "defn.h"

rectangle()
{
    int		hatch;
    float	width, height;
    float	hatch_spacing;
    float	hatch_angle;
    
    if (SIGNED_NUMERIC)
	hatch = getval();
    if (SIGNED_NUMERIC)
	width = getval() * XSCALE;
    if (SIGNED_NUMERIC)
	height = getval() * YSCALE;
    if (SIGNED_NUMERIC)
	hatch_spacing = getval() * XSCALE;
    if (SIGNED_NUMERIC)
	hatch_angle = getval();

    end_draw();
    printf("%g %g M\n", xval, yval);
    printf("%g 0 I\n", width);
    printf("0 %g I\n", height);
    printf("-%g 0 I\n", width);
    printf("closepath stroke\n");
    if (hatch != 2)
        fprintf(stderr, "Warning: Cross hatching not implemented yet\n");
}
