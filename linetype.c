/*
 * Sets the line type and the scaling of the line pattern 
 *
 * Don McCormick CSIRO Division of Applied Physics National Measurements
 * Laboritory Bradfield Road Lindfield 2018 N.S.W. 
 *
 * NOTE: default length for a line pattern is approx 6.5 mm on A4 size paper. 
 */
#include "defn.h"

float   linescale;
int     linestyle;

linetype(line)
int     line;
{
    float   down1, down2;
    float   up1, up2;
    float   diagonal;

    end_draw();

    if (line == LINE_TYPE_SCALE)			/* HP-GL only */
    {
	if (SIGNED_NUMERIC)
	{
	    if ((linestyle = rint(getval())) > 6)
		linestyle = 6;
	    else if (linestyle < -6)
		linestyle = -6;
	}
	else
	{
	    SETDOT = FALSE;
	    printf("[] 0 setdash\n");
	    return;
	}

	diagonal = pow((P2x - P1x),2.0) + pow((P2y - P1y),2.0);
	diagonal = pow(diagonal,0.5);
	if (SIGNED_NUMERIC)
	    linescale = getval() * 0.01 * diagonal * XSCALE * 0.2;
	else
	    linescale = 0.015 * diagonal * XSCALE * 0.2;
    } else
    if (line == LINESCALE)	/* DXY commands only */
    {
	if (SIGNED_NUMERIC)
	    linescale = getval() / 80 * SCALE;
	else
	    return;
    } else
    if (line == LINETYPE)	/* DXY commands only */
    {
	if (SIGNED_NUMERIC)
	{
	    if ((linestyle = rint(getval())) > 5)
		linestyle = 5;
	    else if (linestyle < -5)
		linestyle = -5;
	}
	else
	    return;
    } else
    {
	fprintf(stderr, "Error: Unknown line flag in linetype.c\n");
	exit(1);
    }
    /*
     * select a line style/type and scale/pitch 
     */
    switch (linestyle)
    {
    case 6:
	down1 = 2.0;
	up1 = up2 = 1.5;
	down2 = 1.5;
	break;

    case 5:
	down1 = 3.0;
	up1 = up2 = 1.0;
	down2 = 1.5;
	break;

    case 4:
	down1 = 4.0;
	up1 = up2 = 0.75;
	down2 = 1.0;
	break;

    case 3:
	down1 = 5.0;
	up1 = up2 = 1.0;
	down2 = 0.5;
	break;

    case 2:
	down1 = 5.5;
	up1 = 1.0;
	up2 = down2 = 0.0;
	break;

    case 1:
	down1 = 5.0;
	up1 = 1.5;
	up2 = down2 = 0.0;
	break;

    case -1:
	down1 = 1.5;
	up1 = 3.5;
	down2 = 1.5;
	up2 = 0.0;
	break;

    case -2:
	down1 = 2.0;
	up1 = 2.5;
	down2 = 2.0;
	up2 = 0.0;
	break;

    case -3:
	down1 = 2.5;
	up1 = up2 = 1.75;
	down2 = 0.5;
	break;

    case -4:
	down1 = 2.5;
	up1 = up2 = 1.5;
	down2 = 1.5;
	break;

    case -5:
	down1 = down2 = 2.0;
	up1 = up2 = 1.25;
	break;

    case -6:
	down1 = down2 = 1.75;
	up1 = up2 = 1.5;
	break;
    }
    if (linestyle == 0)
    {
	SETDOT = TRUE;		/* For HP-GL only */
	printf("[] 0 setdash\n");	/* For DXY commands */
    } else
    {
	SETDOT = FALSE;		/* For HP-GL only */
	if (linescale <= 0) linescale = SCALE;
	down1 *= linescale;
	up2 *= linescale;
	up1 *= linescale;
	down2 *= linescale;
	printf("[%g mm %g mm %g mm %g mm] 0 setdash\n",
	       down1, up1, down2, up2);
    }
}
