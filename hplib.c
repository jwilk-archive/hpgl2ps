#include "defn.h"
/****************************************************************************/
/* arcps.c */
/*
 * HPGL supplies the needed arc as:
 *	AA xcenter,ycenter,angle,chord
 *
 * PostScript needs it as:
 *	xcenter ycenter radius start_deg end_deg arc stroke
 *
 * where the drawing starting point has no relationship to the current point,
 * which is set by the HPGL PA command.  The start and ending degree values
 * need to be computed. PostScript arc moves counterclockwise, while arcn
 * moves clockwise from start to end degree locations.
 *
 * A positive HPGL angle means counterclockwise arc, while negative means
 * a clockwise arc (PS arcn).
 *
 * The radius is determined by:
 *	sqrt(x*x + y*y)
 *
 * where x and y are the distances from the current point to the center.
 *
 * The starting offset angle between the current point and the arc center:
 *	180/pi(atan(x/y))  [the atan returns radians]
 *
 * The angle quadrant needs to be determined as well, and will be an offset
 * starting base angle.  The PostScript base is along the X axis, to the right.
 * The angle increases its value in the counterclockwise direction.  It is
 * determined by the signs of the differences between the current point
 * and arc center:
 *	X	Y	start arc
 *	+	+	   90
 *	+	-	    0
 *	-	-	  180
 *	-	+	  270
 */
/****************************************************************************/

void arcps(int type)
{
    float	radius = 0;
    float	angle = 0;
    float	start_deg = 0;
    float	end_deg = 0;
    float	offset_deg = 0;
    float	chord_angle = 0;
    float	Xc = 0;
    float	Yc = 0;
    float	Xdiff = 0;
    float	Ydiff = 0;

    end_draw();

    switch (type)
    {
    case ARCA:
	if (SIGNED_NUMERIC)
	    lastXmove = Xc = getval() * XSCALE + offX;
	if (SIGNED_NUMERIC)
	    lastYmove = Yc = getval() * YSCALE + offY;
	if (SIGNED_NUMERIC)
	    angle = getval();
	if (SIGNED_NUMERIC)
	    chord_angle = getval();
	if (PENDOWN)
	{
	    printf("newpath\n");
	    debugp((stderr,"newpath\n"));
	    printf("  %g %g %s\n", absX, absY, MOVE);
	    debugp((stderr,"  %g %g %s\n", absX, absY, MOVE));
	}
	Xdiff = absX - Xc;
	Ydiff = absY - Yc;
	if (Xdiff < 0 && Ydiff > 0 )
	    offset_deg = 90;
	if (Xdiff < 0 && Ydiff < 0 )
	    offset_deg = 180;
	if (Xdiff > 0 && Ydiff < 0 )
	    offset_deg = 270;
	radius = sqrt(fabs(Xdiff*Xdiff) + fabs(Ydiff*Ydiff));
	if (Xdiff == 0 || Ydiff == 0)
	{
	    if (Ydiff > 0)
		start_deg = 90;
	    if (Xdiff < 0)
		start_deg = 180;
	    if (Ydiff < 0)
		start_deg = 270;
	}
	else if (fabs(Xdiff) < fabs(Ydiff))
	    start_deg = 180/M_PI*(fabs(atan(Xdiff/Ydiff)));
	else
	    start_deg = (180/M_PI*(fabs(atan(Ydiff/Xdiff)))) + 45;
	start_deg += offset_deg;
	if (angle > 0)
	    end_deg = start_deg + angle;
	else
	    end_deg = start_deg - fabs(angle);
	if (end_deg >= 360)
	    end_deg -= 360;
	if (end_deg < 0)
	    end_deg += 360;

	DRAW_FLAG = 1;

	break;

    case ARCR:

	/* BUG: not implemented?? */
	fprintf(stderr,"Relative ARC not implemented\n"); /*EK*/
	break;

    default:

	fprintf(stderr,"Unknown ARC command\n");
	return;
    }
    if (angle < 0)
	AARC = "AAC";
    else
	AARC = "AA";

    printf("%g %g %g %g %g %s\n",Xc,Yc,radius,start_deg,end_deg,AARC);
    debugp((stderr,"%g %g %g %g %g %s\n",Xc,Yc,radius,start_deg,end_deg,AARC));

    debugp((stderr,"\tabsX=%g\tabsY=%g\tXc=%g\tYc=%g\n",absX,absY,Xc,Yc));
    debugp((stderr,"\tXdiff=%g\tYdiff=%g\n",Xdiff,Ydiff));
    debugp((stderr,"\tradius=%g\tstart_deg=%g\tend_deg=%g\tangle=%g\n",radius,start_deg,end_deg,angle));

    /*EK* calculate next "current" point */ 
    absX = Xc + radius * cos(end_deg / (180.0/M_PI));
    absY = Yc + radius * sin(end_deg / (180.0/M_PI));
}

/****************************************************************************/
/* changesizes.c
 * This utility will take a string of real numbers seperated by commas and
 * put them in an array. 
 *
 * Don McCormick 
 */
/****************************************************************************/

#define ERROR1 "Only 9 line sizes allowed"
#define ERROR2 "Too many decimal points in number"
#define ERROR3 "line size specification incorrect"
#define ERROR4 "Max no of characters for each line size is 5"

void changesizes(char sizebuf[50])
{
    int     i;
    int     j = 0;
    int     k = 0;
    int     DECIMAL = 0;
    float   number;
    char    numbuf[5];

    for (i = 0; i < 50; i++)
    {
	if (sizebuf[i] == ',' || sizebuf[i] == '\0')
	{
	    if ((number = atof(numbuf)) >= 0.01 && number <= 10)
		pen_size[j] = number;	/* Put number in array */
	    else
		fprintf(stderr, "Warning: line size too large ignored \n");

	    if (sizebuf[i] == '\0') return;

	    if (j++ > 8)
	    {
		fprintf(stderr, "Error: %s\n", ERROR1);
		exit(1);
	    }
	    for (k = 0; k < 5; k++)
		numbuf[k] = '\0';	/* Clear number buffer */

	    k = 0;
	    DECIMAL = 0;	/* One decimal per number */

	    while (sizebuf[i + 1] == ',' && sizebuf[i + 1] != '\0')
		i++;		/* Get rid of extra commas */
	} else
	{
	    if ((sizebuf[i] >= '0' && sizebuf[i] <= '9')
		|| sizebuf[i] == '.')
	    {
		if (sizebuf[i] == '.')
		{
		    if (DECIMAL == 1)
		    {
			fprintf(stderr, "Error: %s\n", ERROR2);
			exit(1);
		    }
		    DECIMAL = 1;
		}
		numbuf[k] = sizebuf[i];
	    } else
	    {
		fprintf(stderr, "Error: %s\n", ERROR3);
		exit(1);
	    }
	    if (k++ > 5)
	    {
		fprintf(stderr, "Error: %s\n", ERROR4);
		exit(1);
	    }
	}
    }
}

/****************************************************************************/
/* circle.c */
/****************************************************************************/

void circle(int type)
{
    float	radius =0;
    float	start_angle = 0;
    float	end_angle = 360;
    float	chord_angle = 0;
    float	Xc = 0;
    float	Yc = 0;
    float	percent = 0;
    float	distance = 0;
    float	length = 0;
    float	angle = 0;

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
	    absX = Xc = getval() * XSCALE + offX;
	if (SIGNED_NUMERIC)
	    absY = Yc = getval() * YSCALE + offY;
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
	angle = deg_rad * (90.0 - start_angle);
	Xc = absX - radius * cos(angle);
	angle = deg_rad * (90.0 - start_angle);
	Yc = absY + radius * sin(angle);
	break;

    case CCIRCLE:
	if (SIGNED_NUMERIC)
	   absX = getval() * XSCALE;
	if (SIGNED_NUMERIC)
	   absY = getval() * YSCALE;
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
	fprintf(stderr,"Warning: segment and indication lines not available yet\n");
	break;
    }

    printf("%g %g %g %g %g %g Ellipse\n",
		Xc, Yc, radius, radius, start_angle, end_angle);
}


/****************************************************************************/
/* end_draw.c */
/****************************************************************************/

void end_draw(void)
{
    if (DRAW_FLAG)
    {
	if (lastXmove == absX && lastYmove == absY)
	{
	    printf("closepath\n");
	    debugp((stderr,"closepath\n"));
	}
	printf("stroke\n");
	debugp((stderr,"stroke\n"));
	DRAW_FLAG = 0;
    }
    dcount = 0;
}

/****************************************************************************/
/* getval.c
 * Returns a real number 
 */
/****************************************************************************/


#define ERROR "Two or more decimal places in a number"

float getval(void)
{
    char    valbuf[10];
    float   value;
    int     DECIMAL = 0;
    int     i;

    /* Null the value buffer "valbuf" */
    for (i = 0; i < 10; i++)
	valbuf[i] = '\0';

    i = 0;

    ch = getc(stream);

    while ((ch == ' ') || (ch == ','))
    {
	debugp((stderr,"%c",ch));
	ch = getc(stream);
    }

    while ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-' || ch == '+')
    {
	debugp((stderr,"%c",ch));
	if (ch == '.')
	{
	    if (DECIMAL)
	    {
		fprintf(stderr,"Error: %s\n", ERROR);
		exit(1);
	    }
	    DECIMAL = 1;
	}
	valbuf[i++] = ch;
	ch = getc(stream);
    }
    /* remove trailing space or comma to set-up for 
       next digit or mnemonic */
    /* added by Gordon Jacobs so that definition of 
       SIGNED_NUMERIC in defn.h could be made more accurate.
       Solves problem of commands like PA,PD0,0... where
       optional comma is present.  (Tektronix scope outputs!) */ 
    while ((ch == ' ') || (ch == ','))
    {
	debugp((stderr,"%c",ch));
	ch = getc(stream);
    }

    ungetc(ch, stream); 	/* Put non numeric char back */
    value = atof (valbuf);
    return (value);
}

/****************************************************************************/
/* linesize.c */
/****************************************************************************/

void linesize(void)
{
    int 	ipen = 0;
    float	linewidth;

   if (SIGNED_NUMERIC)
	ipen = getval() - 1;

   if (ipen < 0 || ipen > 8)
	ipen = 0;

    pen_number = ipen;

    linewidth = pen_size[ipen] * SCALE; 	/* In mm */
    printf("%g mm setlinewidth\n", linewidth);
}

/****************************************************************************/
/* linetype.c
 * Sets the line type and the scaling of the line pattern 
 *
 * Don McCormick CSIRO Division of Applied Physics National Measurements
 * Laboritory Bradfield Road Lindfield 2018 N.S.W. 
 *
 * NOTE: default length for a line pattern is approx 6.5 mm on A4 size paper. 
 */
/****************************************************************************/


void linetype(int line)
{
    float   down1 = 0;
    float   down2 = 0;
    float   up1   = 0;
    float   up2   = 0;
    float   diagonal = 0;

    float   linescale = 0;
    int     linestyle = 0;

    end_draw();

    if (line == LINE_TYPE_SCALE)			/* HP-GL only */
    {
	if (SIGNED_NUMERIC)
	{
	    if ((linestyle = local_rint(getval())) > 6)
		linestyle = 6;
	    else if (linestyle < -6)
		linestyle = -6;
	}
	else
	{
	    SETDOT = 0;
	    printf("[] 0 setdash\n");
	    return;
	}

	diagonal = pow((xmax - xmin),2.0) + pow((ymax - ymin),2.0);
	diagonal = pow(diagonal,0.5);
	if (SIGNED_NUMERIC)
	    linescale = getval() * 0.01 * diagonal * XSCALE * SCALE * 0.2;
	else
	    linescale = 0.015 * diagonal * XSCALE * SCALE * 0.2;
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
	    if ((linestyle =local_rint(getval())) > 5)
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
	SETDOT = 1;		/* For HP-GL only */
	printf("[] 0 setdash\n");	/* For DXY commands */
    } else
    {
	SETDOT = 0;		/* For HP-GL only */
	if (linescale <= 0) linescale = SCALE;
	down1 *= linescale;
	up2 *= linescale;
	up1 *= linescale;
	down2 *= linescale;
	printf("[%g mm %g mm %g mm %g mm] 0 setdash\n",
	       down1, up1, down2, up2);
    }
}

int local_rint(double x)
{
  int k;
  k = x;
  return(k);
}

/****************************************************************************/
/*	manualfeed.c
 *	A procedure to allow the user to use the manual feed on
 *	the LaserWriter.
 *	The default wait before timeout is 3 minutes however this
 *	is easily changed.
 *
 *	argument: 1.   Enable manual feed.
 *		  0.   Disable manual feed.
 *
 *	Don McCormick
 */
/****************************************************************************/

void manualfeed(int arg)
{
    if (arg == 1)
    {
	printf("statusdict /manualfeed true put\n");
	printf("statusdict /manualfeedtimeout 180 put\n");	/* 3 minute wait */
    } else
	printf("statusdict /manualfeed false put\n");

    printf("usertime 5000 add\n");
    printf("{dup usertime lt {pop exit} if} loop\n");
}

/****************************************************************************/
/* plotcoords.c */
/*
 *	Define default maximum and minimum plotting coordinates.
 *		P1 (xmin, ymin),  P2 (xmax, ymax)
 *
 *	PaperSize can be:
 *			"A3" ISO (420mm by 297mm)
 *			"A4" ISO (297mm by 210mm)
 *			"A"  ANSI (11" by 8.5")
 *			"B"  ANSI (17" by 11")
 *
 *	Mode can be:	"HPGL" or "DXY"
 *
 * Don McCormick
 */
/****************************************************************************/


void plotcoords(void)
{
    if (strcmp(Mode, "HPGL") == 0)
    {
	if (strcmp(PaperSize, "A3") == 0)	/* HP-GL ISO A3 420mm * 297mm */
	{
	    xmax = 15200;
	    ymax = 10800;
	}
	else if(strcmp(PaperSize,"A4") == 0)	/* HP-GL ISO A4 297mm * 210mm */
	{
	    xmax = 10800;
	    ymax = 7680;
	}
	else if(strcmp(PaperSize,"A") == 0)	/* HP-GL ANSI A 11 * 8.5inch */
	{
	    xmax = 10000;
	    ymax = 7200;
	}
	else if(strcmp(PaperSize,"B") == 0)	/* HP-GL ANSI B 17 * 11inch */
	{
	    xmax = 15200;
	    ymax = 10000;
	}
	else 
	{
	    fprintf(stderr,"Illegal paper size\n");
	    exit(-1);
	}
    }
    else
    {
	if (strcmp(PaperSize, "A3") == 0)	/* DXY ISO A3 420mm * 297mm */
	{
	    xmax = 3800;
	    ymax = 2700;
	}
	else				/* DXY ISO A4 297mm * 210mm */
	{
	    xmax = 2700;
	    ymax = 1920;
	}
    }
    /* origin at zero,zero */
    xmin = ymin = 0.0;
    offX = offY = 0.0;
    /* default tick length percentage */
    tlp = tln = 0.005;
}

/****************************************************************************/
/* plotdot.c */
/*
 * Plot a dot or symbol on the paper 
 */
/****************************************************************************/

void plotdot(char *type)
{
    end_draw();

    while (SIGNED_NUMERIC)
    {
	xval = getval() * XSCALE;
	yval = getval() * YSCALE;
	if (type == RMOVE)
	{
	    absX += xval;
	    absY += yval;
	} else
	if (type == MOVE)
	{
	    absX = xval + offX;
	    absY = yval + offY;
	} else
	{
	    fprintf(stderr, "Error: expecting move command not %s\n", type);
	    exit(1);
	}

	if (SYMBOL)
	{
	    printf("%g %g 5 %g (%c) Text\n", absX, absY, char_angle, symbol);
	    debugp((stderr,"%g %g 5 %g (%c) Text\n", absX, absY, char_angle, symbol));
	}
	else if (SETDOT)
	{
	    printf("newpath\n");
	    debugp((stderr,"newpath\n"));
	    printf("  %g %g %s %g %g %s\n", absX, absY, MOVE, absX, absY, DRAW);
	    debugp((stderr,"  %g %g %s %g %g %s\n", absX, absY, MOVE, absX, absY, DRAW));
	    printf("stroke\n");
	    debugp((stderr,"stroke\n"));
	}
    }
}

/****************************************************************************/
/* plotinit.c */
/****************************************************************************/

void plotinit(void)
{
    /*
     * Initialisation of PostScript plot macros 
     */
    MOVE = "M";
    RMOVE = "R";
    DRAW = "D";
    RDRAW = "I";
    AARC = "AA";
    RARC = "RA";

    LANDSCAPE = 1;		/* Display plot in Landscape mode */

    SCALE = 1;			/* Default Scale */

    PLOTABS = 1;		/* Absolute plot coordinates */

    PLOTARC = 0;		/* Plot arc */

    PENDOWN = 0;		/* Penup */

    SETDOT = 0; 		/* HP-GL only for linetype = 0 */

    SYMBOL = 0; 		/* HP-GL only */

    FONT_H_MULT = 1.2;
    FONT_W_MULT = 3.6;		/* necessary for postscript fonts to match */
				/*  when using relative font sizing */
    /*
     *	   Default line/pen sizes (in mm)
     */
    pen_size[0] = 0.0125;
    pen_size[1] = 0.025;
    pen_size[2] = 0.05;
    pen_size[3] = 0.1;
    pen_size[4] = 0.2;
    pen_size[5] = 0.3;
    pen_size[6] = 0.4;
    pen_size[7] = 0.5;
    pen_size[8] = 1.0;

/* I changed the default font to Courier from Helvetica...  The reason */
/* I chose Courier instead of Helvetica is that that was closest match */
/* to what I could describe coming out of my HP 7470A Plotter.	Also, */
/* Helvetica is a *proportional* font, meaning that the width of the */
/* label will not in general match the width of the label when printed */
/* with the plotter. If you want Helvetica (or any other) fine, just */
/* say "-f Helvetica". But in my humble opinion, the Postscript output */
/* should look as close as possible to the plotter output. */
/* Enhancements can be taken as addit'l flags.  -JAS                   */

    (void)sprintf(font,"Courier"); /* Default font */

    EOL = '\003';		/* End of line terminator default */

    /*
     * Default character specifications
     */
    char_angle = 0;		/* Degrees  */
    char_slant = 0;		/* tan(angle) */
/*  ************ modified for larger defaults  GJ  */ 
/*  char_height = 2.7;	*/	/* mm */
/*  char_space = 0.8;	*/	/* mm */
/*  char_width = 1.9;	*/	/* mm */
/*  *********************************************  */
    char_height = 4.0;		/* mm */
    char_space = 1.2;		/* mm */
    char_width = 2.8;		/* mm */

    /*
     * Page offsets set to zero
     */
    xoffset = yoffset = 0;
    /*
     * Define degree to radian parameter
     */
    deg_rad = asin(1.0) / 90.0;
}

/****************************************************************************/
/* plotps.c */
/****************************************************************************/

#define MAXDRAWPOINTS	100

void plotps(char *type)
{
    if (type == MOVE || type == RMOVE)
    {
	while (SIGNED_NUMERIC)
	{
	    if (type == MOVE)
	    {
		end_draw();
		absX = lastXmove = getval() * XSCALE + offX;
		absY = lastYmove = getval() * YSCALE + offY;
	    } else
	    if (type == RMOVE)
	    {
		end_draw();
		lastXmove = absX += getval() * XSCALE ;
		lastYmove = absY += getval() * YSCALE ;
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
		debugp((stderr,"newpath\n"));
		printf("  %g %g %s\n", absX, absY, MOVE);
		debugp((stderr,"  %g %g %s\n", absX, absY, MOVE));
		DRAW_FLAG = 1;
		/* fprintf(stderr, "Warning exceeded %d draw points\n",
			  MAXDRAWPOINTS); */
	    }
	    xval = getval() * XSCALE;
	    yval = getval() * YSCALE;
	    if (!DRAW_FLAG)
	    {
		printf("newpath\n");
		debugp((stderr,"newpath\n"));
		printf("  %g %g %s\n", absX, absY, MOVE);
		debugp((stderr,"  %g %g %s\n", absX, absY, MOVE));
		DRAW_FLAG = 1;
	    }
	    if (type == RDRAW)
	    {
		absX += xval;
		absY += yval;
		printf("  %g %g %s\n", xval, yval, RDRAW);
		debugp((stderr,"  %g %g %s\n", xval, yval, RDRAW));
	    } else
	    if (type == DRAW)
	    {
		absX = xval + offX;
		absY = yval + offY;
		printf("  %g %g %s\n", absX, absY, DRAW);
		debugp((stderr,"  %g %g %s\n", absX, absY, DRAW));
	    } else
	    {
		fprintf(stderr, "Error: expecting draw command not %s\n", type);
		exit(1);
	    }
	}
    }
}

/****************************************************************************/
/* ps_macros() */
/****************************************************************************/

void ps_macros(void)
{
    printf("%%! PS-Adobe-1.0: For Apple LaserWriter\n");
    printf("%% default font is 14 pt. Helvetica\n");
/*    printf("/basefont {/Helvetica findfont 14 scalefont setfont} def\n"); */
/*    printf("/basefont {/Courier findfont 14 scalefont setfont} def\n");   */
/* This changed so that user can pick their font. -JAS. */
    printf("/basefont {/%s findfont 14 scalefont setfont} def\n", font);

/*  printf("/mm {72.27 mul 25.4 div} def\n");*/ /* Specify millimeters */
    printf("/mm {72.0 mul 25.4 div} def\n");	/* Specify millimeters */

    printf("/M\n");				/* Move macro */
    printf("{\n");
    printf("    /Ymove exch def\n");
    printf("    /Xmove exch def\n");
    printf("    Xmove mm Ymove mm moveto\n");
    printf("} def\n");

    printf("/R\n");				/* Relative move macro */
    printf("{\n");
    printf("    /Yrmove exch def\n");
    printf("    /Xrmove exch def\n");
    printf("    Xrmove mm Yrmove mm rmoveto\n");
    printf("} def\n");

    printf("/D\n");				/* Draw macro */
    printf("{\n");
    printf("    /Ydraw exch def\n");
    printf("    /Xdraw exch def\n");
    printf("    Xdraw mm Ydraw mm lineto\n");
    printf("} def\n");

    printf("/I\n");				/* Relative draw macro */
    printf("{\n");
    printf("    /Yrdraw exch def\n");
    printf("    /Xrdraw exch def\n");
    printf("    Xrdraw mm Yrdraw mm rlineto\n");
    printf("} def\n");

    printf("/AA\n");				/* Arc draw macro */
    printf("{\n");
    printf("    /endangle exch def\n");
    printf("    /startangle exch def\n");
    printf("    /radius exch def\n");
    printf("    /Ydraw exch def\n");
    printf("    /Xdraw exch def\n");
    printf("    Xdraw mm Ydraw mm radius mm startangle endangle arc\n");
    printf("} def\n");

    printf("/AAC\n");				/* Arc draw macro (clockwise) */
    printf("{\n");
    printf("    /endangle exch def\n");
    printf("    /startangle exch def\n");
    printf("    /radius exch def\n");
    printf("    /Ydraw exch def\n");
    printf("    /Xdraw exch def\n");
    printf("    Xdraw mm Ydraw mm radius mm startangle endangle arcn\n");
    printf("} def\n");
    /*
     *		Procedure to change font and size of font
     *		---->	font size Font	  <----
     */
    printf("/Font\n");
    printf("{\n");
    printf("    /Height exch def\n");
    printf("    /FontName exch def\n");
    printf("    FontName findfont Height mm scalefont setfont\n");
    printf("} def\n");
    /*
     *		Procedure to change font, width, slant and height
     *		---->	font width height slant DefFont    <----
     *
     *	Note: slant = height * tan( slant_angle )
     */
    printf("/DefFont\n");
    printf("{\n");
    printf("    /Slant exch def\n");
    printf("    /Height exch def\n");
    printf("    /Width exch def\n");
    printf("    /FontName exch def\n");
    printf("    FontName findfont [ Width mm 0 Slant mm Height mm 0 0] makefont setfont\n");
    printf("} def\n");
    /*
     *		General Text Layout Procedure
     *		---->	x y pos_num angle (text) Text	 <----
     */
    printf("/Text\n");
    printf("{\n");
    printf("    /String exch def\n");
    printf("    /Angle exch def\n");
    printf("    /Position exch def\n");
    printf("    /Ymove exch def\n");
    printf("    /Xmove exch def\n");
    printf("    Position 1 lt {/hpf 0 def /lpf 0 def} if\n");
    printf("    Position 1 eq {/hpf 0 def /lpf 0 def} if\n");
    printf("    Position 2 eq {/hpf 0 def /lpf 0.5 def} if\n");
    printf("    Position 3 eq {/hpf 0 def /lpf 1 def} if\n");
    printf("    Position 4 eq {/hpf 0.5 def /lpf 0 def} if\n");
    printf("    Position 5 eq {/hpf 0.5 def /lpf 0.5 def} if\n");
    printf("    Position 6 eq {/hpf 0.5 def /lpf 1 def} if\n");
    printf("    Position 7 eq {/hpf 1 def /lpf 0 def} if\n");
    printf("    Position 8 eq {/hpf 1 def /lpf 0.5 def} if\n");
    printf("    Position 9 eq {/hpf 1 def /lpf 1 def} if\n");
    printf("    Position 9 gt {/hpf 1 def /lpf 1 def} if\n");
    printf("    /StrLen String stringwidth pop lpf mul def\n");
    printf("    /StrHt Height mm hpf mul def\n");
    printf("    /Xdiff StrHt Angle sin mul StrLen Angle cos mul sub def\n");
    printf("    /Ydiff StrHt Angle cos mul StrLen Angle sin mul add def\n");
    printf("    Xmove mm Xdiff add Ymove mm Ydiff sub moveto\n");
    printf("    gsave\n");
    printf("        Angle rotate\n");
    printf("        String show\n");
    printf("    grestore\n");
    printf("    /PosterOnly 0 def\n");
    printf("} def\n");
    /*
     *		Ellipse and Circle procedure.
     *	---->	xcen ycen xrad yrad start_angle end_angle Ellipse   <----
     */
    printf("/EllipseDict 8 dict def\n");
    printf("EllipseDict /mtrx matrix put\n");
    printf("/Ellipse \n");
    printf("{   EllipseDict begin\n");
    printf("    /endangle exch def\n");
    printf("    /startangle exch def\n");
    printf("    /yradius exch def\n");
    printf("    /xradius exch def\n");
    printf("    /ycenter exch def\n");
    printf("    /xcenter exch def\n");
    printf("    /savematrix mtrx currentmatrix def\n");
    printf("    xcenter mm ycenter mm translate\n");
    printf("    xradius mm yradius mm div 1 scale\n");
    printf("    newpath\n");
    printf("        0 0 xradius mm startangle endangle arc\n");
    printf("    stroke\n");
    printf("    savematrix setmatrix\n");
    printf("    end\n");
    printf("} def\n");

    printf("basefont\n");		/* Set the default font */
    printf("1 setlinecap\n");		/* Use round caps */
    printf("1 setlinejoin\n");		/* Use round joins */
    printf("3 setmiterlimit\n");	/* Bevel small angle miters */
}

/****************************************************************************/
/* rectangle.c */
/****************************************************************************/

void rectangle(void)
{
    int 	hatch = 0;
    float	width = 0;
    float	height = 0;
    float	hatch_spacing = 0;
    float	hatch_angle = 0;
    
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
	notimp((stderr, "\nNot implemented: Cross hatching (rectangle.c)"));
}

/****************************************************************************/
/* textps.c */
/****************************************************************************/

#define MAXBUFSIZE 100

void textps(int type)
{
    char    string[4];
    char    buffer[MAXBUFSIZE];
/*  Unused, so commented out. -jas */
/*  float   Xch, Ych;		   */
    int     intval;
    int     i;

    end_draw();

    if (type == TEXT)
    {
	for (i = 0 ; i < MAXBUFSIZE; i++)	/* Clear buffer */
	    buffer[i] = '\0';

	i = 0;					/* Reset buffer counter */

	while (((ch = getc(stream)) != EOF)
			&& ch != CR && ch != LF && ch != EOL) {
	    buffer[i++] = ch;
	}

	printf("%g %g 1 %g (%s) Text\n", absX, absY, char_angle, buffer);

	/* move to end of string */
	absX += (i * (char_space)) * cos(char_angle * deg_rad) ;
	absY += (i * (char_space)) * sin(char_angle * deg_rad) ;

    } else			/* Must be a MARK */
    {
	int	symb_num = 0;

/* Running gcc -Wall discovered this, so I commented out these three lines */
/* and substituted the single following line.				   */
/*	if (SIGNED_NUMERIC)						   */
/*	    symb_num = getval();					   */
/*	else								   */
	if (!SIGNED_NUMERIC)	 /*  <--SUBSTITUTION  */
	  {
	    symb_num = getval();
	    fprintf(stderr,
		    "Error: expecting a symbol number not %c (%d)",
		    symb_num, symb_num);
	    exit(1);
	  }
	intval = (int)(getval() + 0.5);
	switch (intval)
	{
	case 0:
	    strcpy(string, "*");
	    break;

	case 1:
	    strcpy(string, "+");
	    break;

	case 2:
	    strcpy(string, "#");
	    break;

	case 3:
	    strcpy(string, "@");
	    break;

	case 4:
	    strcpy(string, "%");
	    break;

	case 5:
	    strcpy(string, "|");
	    break;

	case 6:
	    strcpy(string, "=");
	    break;

	case 7:
	    strcpy(string, "&");
	    break;

	case 9:
	    strcpy(string, "O");
	    break;

	case 10:
	    strcpy(string, "0");
	    break;

	case 11:
	    strcpy(string, "Y");
	    break;

	case 12:
	    strcpy(string, "X");
	    break;

	case 13:
	    strcpy(string, "Z");
	    break;

	case 14:
	    strcpy(string, "S");
	    break;

	case 15:
	    strcpy(string, "Q");
	    break;

	default:
	    fprintf(stderr, "Warning symbol number is %d\n", symb_num);
	    strcpy(string, "*");
	    break;
	}
	printf("%g %g 5 %g (%s) Text\n", absX, absY, char_angle, string);
    }
}

/****************************************************************************/
/* tick.c */
/*
 * tick(type)
 *
 * function for handling the XT,YT commands 
 * in Hewlett-Packard Graphics Language (HP-GL).
 *
 * Written by Gordon Jacobs 
 * University of California, Berkeley , Dept of EECS.
 */
/****************************************************************************/


void tick(int type)
{
    float Xtlengthp,Xtlengthn,Ytlengthp,Ytlengthn;

    /* Compute tick lengths as a function of viewport dimensions */
    /* Xticks are in Y direction: */
    Xtlengthp = tlp * (ymax - ymin) * XSCALE; 
    Xtlengthn = tln * (ymax - ymin) * XSCALE; 
    /* Yticks are in X direction */
    Ytlengthp = tlp * (xmax - xmin) * YSCALE; 
    Ytlengthn = tln * (xmax - xmin) * YSCALE; 

    /* Ticks: Don't mess with position pointers,
     *	 just use relative draw and move commands 
     */
    if (type == XTICK) {
	if(tlp != 0.0) {
		lastYmove = absY += Xtlengthp;
		printf("  %g %g %s\n",0.0,Xtlengthp,RMOVE);
		printf("  %g %g %s\n",0.0,-Xtlengthp,RDRAW);
	}
	if(tln != 0.0) {
		lastYmove = absY -= Xtlengthp;
		printf("  %g %g %s\n",0.0,-Xtlengthn,RMOVE);
		printf("  %g %g %s\n",0.0,Xtlengthn,RDRAW);
	}
    }
    else {
	if(tlp != 0.0) {
		lastXmove = absX += Xtlengthp;
		printf("  %g %g %s\n",Ytlengthp,0.0,RMOVE);
		printf("  %g %g %s\n",-Ytlengthp,0.0,RDRAW);
	}
	if(tln != 0.0) {
		lastXmove = absX -= Xtlengthp;
		printf("  %g %g %s\n",-Ytlengthn,0.0,RMOVE);
		printf("  %g %g %s\n",Ytlengthn,0.0,RDRAW);
	}
    }
}

/****************************************************************************/
/* userdefchar.c */
/*
 * userdefchar(type)
 *
 * function for handling the USER DEFINED CHARACTER (UC) command
 * in Hewlett-Packard Graphics Language (HP-GL).
 *
 * Written by Gerald William Kokodyniak B.A.Sc. M.A.Sc.
 * University of Toronto, Department of Mechanical Engineering
 *
 * Heavily modified by Gordon Jacobs, University of Calif, Berkeley
 *  Now scales user character size to that of regular characters
 *  Orients user character the same as regular characters
 *  Linewidth chosed to always be 0.25mm to better match
 *  postscript font.
 *
 */
/****************************************************************************/

#define MAXDRAWPOINTS	100

/* standard resolution user-def character pen control numbers */
/*     for enhanced, change to -9999,9999 */
#define PENUPCTL -99.0
#define PENDNCTL  99.0

/* linewidth in mm for user defined characters */
#define DEFCHAR_LINEWIDTH 0.25

/* Scaling parameters */
#define CHAR_CELL_H  5.0
#define CHAR_CELL_W  2.5

void userdefchar(void)
{
    float   number, rad, angl;
/*  Now externally declared. -jas.	       */
/*  float   theMagnitude(), theAngle();        */
/*  These are unused, so commented out.  -jas  */
/*  float first_absX = absX;		       */
/*  float first_absY = absY;		       */
/*  float tmp;				       */
    PENDOWN = 0;
    printf("%g mm setlinewidth\n", DEFCHAR_LINEWIDTH);

    while (SIGNED_NUMERIC)
    {
	number = getval();
	if (number >= PENDNCTL) {
	    PENDOWN = 1;
	    number = getval();
	}
	else if (number <= PENUPCTL) {
	    PENDOWN = 0;
	    number = getval();
	}

	if (number < PENDNCTL && number > PENUPCTL) {
	    if (PENDOWN) {
		if (dcount++ >= MAXDRAWPOINTS) {
		    end_draw();
		    printf("newpath\n");
		    printf("  %g %g %s\n", absX, absY, MOVE);
		    DRAW_FLAG = 1;
		}
		xval = number / CHAR_CELL_W * char_width * XSCALE;
		yval = getval() / CHAR_CELL_H * char_height * YSCALE;
		if (!DRAW_FLAG) {
		    printf("newpath\n");
		    printf("  %g %g %s\n", absX, absY, MOVE);
		    DRAW_FLAG = 1;
		}
		/* perform rotation */
		rad = theMagnitude(xval,yval);
		angl = theAngle(xval,yval);
		angl += char_angle * deg_rad;
		xval =	rad *cos(angl);
		yval =	rad *sin(angl);
		absX += xval;
		absY += yval;
		printf("  %g %g %s\n", xval, yval, RDRAW);
	    } else {
		end_draw();
		xval = number  / CHAR_CELL_W * char_width *XSCALE;
		yval = getval() / CHAR_CELL_H * char_height * YSCALE;

		rad = theMagnitude(xval,yval);
		angl = theAngle(xval,yval);
		angl += char_angle * deg_rad;

		lastXmove = absX += rad * cos(angl);
		lastYmove = absY += rad * sin(angl);
	    }
	}
	else {
	    if(number >= PENDNCTL)
		PENDOWN = 1;
	    else if(number <= PENUPCTL)
		PENDOWN = 0;
	}
    }
    PENDOWN = 0;
    end_draw();
    /* move a fraction of a space so next character doesn't abutt */
    absX += 0.2 * char_space * cos(char_angle * deg_rad);
    absY += 0.2 * char_space * sin(char_angle * deg_rad);
    printf("%g mm setlinewidth\n", pen_size[pen_number]);
}

float theMagnitude(float x, float y)
{
    return(sqrt(x * x + y * y));
}

float theAngle(float x, float y)
{
    if(x != 0.0)
	return(atan(y/x));
    else
	return((y > 0.0) ? M_PI_2 : (M_PI + M_PI_2));
}

/****************************************************************************/
/* viewport.c */
/*
 * This procedure sets up the variables for the translation of plotter
 * coordinates to PostScript coordinates.
 *
 * Note: the procedure "defaults" may be incorporated here, however
 *	I have not had the time to work it out properly.
 *
 * Don McCormick
 */
/****************************************************************************/

/*  original psxmax */
#define XWIDTH 0.90

void viewport(void)
{
    /* original values for A4 */
    /* float pagewidth = 197.0; */	/* Page width for Laser Printer  */
    /* float pageheight = 280.0; */	/* Page height for Laser Printer */
    /* float pwoffset = 12; */
    /* float phoffset = 12; */

    /*	8.5 x 11 inch paper */
    float pagewidth = 200.0;		/* Page width for Laser Printer */
    float pageheight = 265.0;		/* Page height for Laser Printer */
    float pwoffset = 28;
    float phoffset = 6;
    /* values above selected empirically to match HP7550A plot -G.J. */

    /* made global */
    /* float psxmax, psymax;	*/	/* Sizes scaled to the viewport */

    if (LANDSCAPE)		/* Default mode */
    {
	psymax = pagewidth * XWIDTH;
	psxmax = psymax * (xmax - xmin)/ (ymax - ymin);
	xoffset += (pageheight + phoffset - psxmax) / 2.0;
	yoffset -= (pagewidth + pwoffset + psymax) / 2.0;
	printf("90 rotate\n"); 
    } else
    {
	psxmax = pagewidth * XWIDTH;
	psymax = psxmax * (ymax - ymin) / (xmax - xmin);
	xoffset += (pagewidth + pwoffset - psxmax) / 2.0;
	yoffset += (pageheight + phoffset - psymax) / 2.0;
    }
    printf("%g mm %g mm translate\n", xoffset, yoffset);
    XSCALE = psxmax / (xmax - xmin) * SCALE;
    YSCALE = psymax / (ymax - ymin) * SCALE;
    /* fprintf(stderr,"Xscale = %g  Yscale = %g\n",XSCALE,YSCALE); */
}

/* function called when the HP-GL Scale command is received */
/* Modifies the X,Y SCALE factors and the origin offsets */
/*  Added by Gordon Jacobs */

void modify_viewport(void)
{
    /* re-calculate scale parameters */
    XSCALE = psxmax / (xmax - xmin) * SCALE;
    YSCALE = psymax / (ymax - ymin) * SCALE;

    /* calculate new offset */
    offX = -xmin * XSCALE;
    offY = -ymin * YSCALE;

    debugp((stderr,"MODIFY: Xscale = %g  Yscale = %g\n",XSCALE,YSCALE));
    debugp((stderr,"OFFSET: offX = %g  offY = %g\n",offX,offY));
}
/****************************************************************************/
/****************************************************************************/
