#include "defn.h"

circle(type)
int	type;
{
    float	radius;
    float	start_angle = 0;
    float	end_angle = 360;
    float	chord_angle = 0;
    float	Xc, Yc;
    float	percent;
    float	distance;
    float	length;
    float	angle;

    end_draw();

    switch (type)
    {
    case RDGLCIRCLE:
	if (SIGNED_NUMERIC)
	    radius = getval() * XSCALE;
	if (SIGNED_NUMERIC)
	    chord_angle = getval();
	Xc = absX;
	Yc = absY;
	break;

    case CIRCLE:
	if (SIGNED_NUMERIC)
	    absX = Xc = getval() * XSCALE + XOFFSET;
	if (SIGNED_NUMERIC)
	    absY = Yc = getval() * YSCALE + YOFFSET;
	if (SIGNED_NUMERIC)
	    radius = getval() * XSCALE;
	if (SIGNED_NUMERIC)
	    start_angle = getval();
	if (SIGNED_NUMERIC)
	    end_angle = getval();
	if (SIGNED_NUMERIC)
	    chord_angle = getval();
	break;

    case RCIRCLE:
	if (SIGNED_NUMERIC)
	    radius = getval() * XSCALE;
	if (SIGNED_NUMERIC)
	    start_angle = getval();
	if (SIGNED_NUMERIC)
	    end_angle = getval();
	if (SIGNED_NUMERIC)
	    chord_angle = getval();
	angle = deg2rad * (90.0 - start_angle);
	Xc = absX - radius * cos(angle);
	angle = deg2rad * (90.0 - start_angle);
	Yc = absY + radius * sin(angle);
	break;

    case CCIRCLE:
	if (SIGNED_NUMERIC)
	   absX = getval() * XSCALE + XOFFSET;
	if (SIGNED_NUMERIC)
	   absY = getval() * YSCALE + YOFFSET;
	break;

    case ACIRCLE:
	Xc = absX;
	Yc = absY;
	if (SIGNED_NUMERIC)
	    radius = getval() * XSCALE;
	if (SIGNED_NUMERIC)
	    start_angle = getval();
	if (SIGNED_NUMERIC)
	    end_angle = getval();
	if (SIGNED_NUMERIC)
	    chord_angle = getval();
	break;

    case SCIRCLE:
	if (SIGNED_NUMERIC)
	    percent = getval();
	if (SIGNED_NUMERIC)
	    distance = getval();
	if (SIGNED_NUMERIC)
	    length = getval();
	fprintf(stderr,
		"Warning: segment and indication lines not available yet\n");
	break;
    }

    printf("%g %g %g %g %g %g Ellipse\n",
		Xc, Yc, radius, radius, start_angle, end_angle);
}
