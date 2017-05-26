/* hpglcom.c */
/*
 * This procedure translates RD-GL (Roland DG Graphic Language) into the
 * equivalent PostScript language. 
 *
 * The RD-GL is a superset equivalent to HP-GL 
 *
 * Don McCormick 
 *
 * Extensively modified by Michael L. Brown.
 *
 * The parser didn't get rid of the characters, up to the next possible
 * HPGL command.  Added a DEBUG, so that the commands that aren't known
 * are sent to the stderr.  By making this compilable, the screen isn't
 * clutterd with all of the many possible HPGL commands that aren't being
 * operated on.
 */

#include "hplib.c"

/* The folowing defaults should be 0.5% and 1.0% for the respective  character
 * width and height, however this is too small when scaled to Postcript
 * charcter sizes.
 */
float DEFWIDTH = 0.0075;	/* 0.75 % of P2x - P1x for default char width */
float DEFHEIGHT = 0.015;	/* 1.5 % of P2y - P1y for default char height */
/*
 * Values above are further multiplied by FONT_W_MULT and FONT_H_MULT
 * which can be set on command line. Defaults are 4.0 and 1.1
 * Added for better matching of relative font sizes to plotter results 
 */

#define SPACE_FACTOR 0.64  /* used in computation of a character space */

#define TWOCH(c1,c2) ((toupper(c1)<<8)|toupper(c2))

void hpglcom(char op1)
{
    char    op2;

#if 0
    op2 = getc(stream);
    switch (TWOCH(op1,op2))
#endif
    switch (op1)
    {
    case 'A':
    case 'a':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Arc Absolute */
	case 'a':
	    debugp((stderr,"%c%c",op1,op2));
	    PLOTARC = 1;
	    if (PENDOWN)
	    {
		if (SIGNED_NUMERIC)
		{
		    if (SETDOT)
			plotdot(MOVE);
		    else if (PLOTABS)
			arcps(ARCA);
		    else
			arcps(ARCR);
		}
	    }
	    dumpit(1);
	    break;

	case 'F':		/* Advance Full Page */
	case 'f':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'H':		/* Advance Half Page */
	case 'h':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'P':		/* Automatic Pen Lift (HP-GL only) */
	case 'p':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'R':		/* Arc Relative */
	case 'r':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'S':		/* Acceleration Select */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "%c%c: Warning: Unknown HP-GL Command\n\n", op1,op2));
	    dumpit(2);
	}
	break;

    case 'B':
    case 'b':
	op2 = getc(stream);
	switch (op2)
	{
	case 'L':		/* Buffered Label String */
	case 'l':
	    while (((ch = getc(stream)) != EOF) && ch != EOL);
	    notimp((stderr, "Not Implemented: %c%c",op1,op2));
	    break;

	default:
	    notimp((stderr, "%c%c: Warning: Unknown HP-GL Command\n\n", op1,op2));
	    dumpit(2);
	}
	break;

    case 'C':
    case 'c':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Alternate Character Set (Not Used) */
	case 'a':
	    notimp((stderr, "Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'C':		/* Character Chord Angle */
	case 'c':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'I':		/* Circle */
	case 'i':
	    debugp((stderr,"%c%c",op1,op2));
	    circle(RDGLCIRCLE);
	    break;

	case 'M':		/* Character Selection Mode */
	case 'm':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'P':		/* Character Plot */
	case 'p':
	    debugp((stderr,"%c%c",op1,op2));
	    {
		float	xspace, yspace;

		xspace = getval() * XSCALE * SCALE * (char_width + char_space);
		yspace = getval() * YSCALE * SCALE * (char_width + char_space);
		end_draw();
		printf("    %g mm %g mm %s\n", xspace, yspace, RMOVE);
	    }
	    break;

	case 'S':		/* Standard Character Set */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'T':		/* Chord Tolerance */
	case 't':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'D':
    case 'd':
	op2 = getc(stream);
	switch (op2)
	{
	case 'C':		/* Digitize Clear (Not Used) */
	case 'c':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'F':		/* Default */
	case 'f':
	    debugp((stderr,"%c%c",op1,op2));
	    SETDOT = 0;
	    SYMBOL = 0;
	    PENDOWN = 0;
	    EOL = '\003';
	    char_angle = 0;
	    char_slant = 0;
	    if(LANDSCAPE) {
		/*EK* BUG: added FNOT_H_MULT, unsure about _W_ */
		char_width = DEFWIDTH * FONT_W_MULT * (ymax - ymin) * YSCALE * SCALE;
		char_height = DEFHEIGHT * FONT_H_MULT * (xmax - xmin) * XSCALE * SCALE;
	    }
	    else {
		char_width = DEFWIDTH * FONT_W_MULT * (xmax - xmin) * XSCALE * SCALE;
		char_height = DEFHEIGHT * FONT_H_MULT * (ymax - ymin) * YSCALE * SCALE;
	    }
	    char_space = char_width * (1/SPACE_FACTOR - 1);
	 /* fprintf(stderr,"DF h=%g\n",char_height); **EK*/
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant);
	    dumpit(1);
	    break;

	case 'I':		/* Absolute Direction */
	case 'i':
	    debugp((stderr,"%c%c",op1,op2));
	    {
		float	run, rise;

		if (SIGNED_NUMERIC)
		{
		    run = getval() * XSCALE;
		    rise = getval() * YSCALE;
		    char_angle = atan2(rise, run) / deg_rad;
		}
		else
		    char_angle = 0;
	    }
	    break;

	case 'L':		/* Downloadable Character */
	case 'l':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'P':		/* Digitize Point (Not Used) */
	case 'p':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'R':		/* Relative Direction */
	case 'r':
	    debugp((stderr,"%c%c",op1,op2));
	    {
		float	run, rise;

		if (SIGNED_NUMERIC)
		{
		    run = getval() * XSCALE;
		    rise = getval() * YSCALE;
		    char_angle += atan2(rise, run) / deg_rad;
		}
		else
		    char_angle = 0;
	    }
	    break;

	case 'S':		/* Designate Character Set into Slot*/
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'T':		/* Define Terminator */
	case 't':
	    debugp((stderr,"%c%c",op1,op2));
	    if ((ch = getc(stream)) != EOF)
		EOL = ch;	/* End of label terminator */
	    dumpit(1);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'E':
    case 'e':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Edge Rectangle Absolute */
	case 'a':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'C':		/* Enable Cut Line */
	case 'c':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'P':		/* Edge Polygon */
	case 'p':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'R':		/* Edge Rectangle Relative */
	case 'r':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'S':		/* Extra Space */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'W':		/* Edge Wedge */
	case 'w':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown RD-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'F':
    case 'f':
	op2 = getc(stream);
	switch (op2)
	{
	case 'P':		/* Fill Polygon */
	case 'p':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'R':		/* Advance Frame */
	case 'r':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'S':		/* Force Select */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'T':		/* Fill Type */
	case 't':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'G':
    case 'g':
	op2 = getc(stream);
	switch (op2)
	{
	case 'P':		/* Group Pen */
	case 'p':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'I':
    case 'i':
	op2 = getc(stream);
	switch (op2)
	{
	case 'M':		/* Input Mask (Not Used) */
	case 'm':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'N':		/* Initialize */
	case 'n':
	    debugp((stderr,"%c%c",op1,op2));
	    plotcoords();
	    SETDOT = 0;
	    SYMBOL = 0;
	    PENDOWN = 0;
	    EOL = '\003';
	    char_angle = 0;
	    char_slant = 0;
	    if(LANDSCAPE) {
		char_width = DEFWIDTH * FONT_W_MULT * (ymax - ymin) * YSCALE * SCALE;
		char_height = DEFHEIGHT * FONT_H_MULT * (xmax - xmin) * XSCALE * SCALE;
	    }
	    else {
		char_width = DEFWIDTH * FONT_W_MULT * (xmax - xmin) * XSCALE * SCALE;
		char_height = DEFHEIGHT * FONT_H_MULT * (ymax - ymin) * YSCALE * SCALE;
	    }
	    char_space = char_width * (1/SPACE_FACTOR - 1);
	 /* fprintf(stderr,"IN h=%g\n",char_height); **EK*/
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant);
	    dumpit(1);
	    break;

	case 'P':		/* Input P1 and P2 (Not Used) */
	case 'p':
	    /*EK* BUG: sometimes "IP;;", sometimes "IP0,0,9310,6860;" */
	    debugp((stderr,"IP Not Implemented"));
	    dumpit(1);
	    break;

	case 'V':		/* Invoke Character Slot */
	case 'v':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'W':		/* Input Window */
	case 'w':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'L':
    case 'l':
	op2 = getc(stream);
	switch (op2)
	{
	case 'B':		/* Label */
	case 'b':
/* I removed this going from 2.0 to 2.1. It looks incorrect. As far as I  */
/* can tell textps(TEXT) does output the label unless they are speaking   */
/* of some enhancement I dont know of.	-jas. 94/11/9			  */
/*	    notimp((stderr,"Not Implemented: %c%c",op1,op2));		  */
	    textps(TEXT);
	    break;

	case 'O':		/* Label Origin */
	case 'o':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'T':		/* Line Type */
	case 't':
	    debugp((stderr,"%c%c",op1,op2));
	    linetype(LINE_TYPE_SCALE);
	    dumpit(1);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'N':
    case 'n':
	op2 = getc(stream);
	switch (op2)
	{
	case 'R':		/* Not Ready */
	case 'r':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'O':			/* NOT USED */
    case 'o':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Output Actual Position */
	case 'a':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'C':		/* Output Commanded Position */
	case 'c':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'D':		/* Output Digitise */
	case 'd':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'E':		/* Output Error */
	case 'e':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'F':		/* Output Factors */
	case 'f':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'H':		/* Output Hard-Clip Limits */
	case 'h':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'I':		/* Output Indentification */
	case 'i':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'L':		/* Output Label Length */
	case 'l':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'O':		/* Output Options */
	case 'o':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'P':		/* Output P1 and P2 */
	case 'p':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'S':		/* Output Status */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'T':		/* Output Carousel Type */
	case 't':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'W':		/* Output Window */
	case 'w':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'P':
    case 'p':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Plot Absolute */
	case 'a':
	    debugp((stderr,"%c%c",op1,op2));
	    dumpcomma();
	    PLOTABS = 1;
	    if (SIGNED_NUMERIC)
	    {
		if (SETDOT || SYMBOL)
		    plotdot(MOVE);
		else if (PENDOWN)
		    plotps(DRAW);
		else
		    plotps(MOVE);
	    }
	    dumpit(1);
	    break;

	case 'B':		/* Print Buffered Label */
	case 'b':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'D':		/* Pen Down */
	case 'd':
	    debugp((stderr,"%c%c",op1,op2));
	    dumpcomma();
	    PENDOWN = 1;
	    if (SIGNED_NUMERIC)
	    {
		if (SETDOT)
		    plotdot(MOVE);
		else if (PLOTABS)
		    plotps(DRAW);
		else 
		    plotps(RDRAW);
	    }
	    dumpit(1);
	    break;

	case 'G':		/* Advance Full Page */
	case 'g':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'M':		/* Polygon Mode */
	case 'm':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'R':		/* Plot Relative */
	case 'r':
	    debugp((stderr,"%c%c",op1,op2));
	    PLOTABS = 0;
	    if (SIGNED_NUMERIC)
	    {
		if (SETDOT || SYMBOL)
		    plotdot(RMOVE);
		else if (PENDOWN)
		    plotps(RDRAW);
		else
		    plotps(RMOVE);
	    }
	    dumpit(1);
	    break;

	case 'T':		/* Pen Thickness */
	case 't':
	    debugp((stderr,"%c%c",op1,op2));
	    {
		float	linewidth;

		linewidth = getval() * SCALE;		/* In mm */
		printf("%g mm setlinewidth\n", linewidth);
	    }
	    dumpit(1);
	    break;

	case 'U':		/* Pen Up */
	case 'u':
	    debugp((stderr,"%c%c",op1,op2));
	    PENDOWN = 0;
	    if (SIGNED_NUMERIC)
	    {
		if (SETDOT)
		    plotdot(MOVE);
		else if (PLOTABS)
		    plotps(MOVE);
		else
		    plotps(RMOVE);
	    }
	    dumpit(1);
	    break;

	case 'S':		/* PS: Paper Size *EK*/
	case 's':
	    debugp((stderr,"%c%c",op1,op2));
	    /* BUG: ignore "Paper Size" */
	    /* BUG: typical arguments: 15510,9897 */
	    dumpit(1);
	    break;
 
	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'R':
    case 'r':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Fill Rectange Absolute */
	case 'a':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'O':		/* Rotate Coordinate System */
	case 'o':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'R':		/* Fill Rectangle Relative */
	case 'r':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown RD-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'S':
    case 's':
	op2 = getc(stream);
	switch (op2)
	{
	case 'A':		/* Select Alternate Set */
	case 'a':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'C':		/* Scale */
	case 'c':		/* Scaling added by Gordon Jacobs */
	    debugp((stderr,"%c%c",op1,op2));
	    if (SIGNED_NUMERIC){
		xmin = getval();
	    }
	    else {
		dumpit(1);
		break;
	    }

	    if (SIGNED_NUMERIC) {
		xmax = getval();
	    }
	    if (SIGNED_NUMERIC) {
		ymin = getval();
	    }
	    if (SIGNED_NUMERIC) {
		ymax = getval();
	    }
	    modify_viewport();	/* new function for scaling */
	    end_draw();
	    dumpit(1);
	    break;

	case 'G':		/* Select Pen Group */
	case 'g':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	case 'I':		/* Absolute Character Size (SI) */
	case 'i':
	    debugp((stderr,"%c%c",op1,op2));
	    if (SIGNED_NUMERIC)
	      {
/*		char_width  = getval() * 10 * SCALE;		   In mm */
/* Below changed by me to get an exact match between the plotter and the */
/* PostScript printer output as far as width.  It assumes a standard	 */
/* Courier default, but should work with all other fonts, too.	-JAS.	 */
/* BUG: seems to generate too small characters, so added multiplier *EK* */
		char_width  = getval() * FONT_W_MULT * 10 * 1.25 * SCALE; /* In mm */
		char_height = getval() * FONT_H_MULT * 10 * SCALE; /* In mm */
	      }
	    else
	      {
		if ((ch = getc(stream)) == ';')
		  {
		    char_width = FONT_W_MULT * 2.7 * SCALE;
		    char_height = FONT_H_MULT * 1.9 * SCALE;
		  }
	      }
	    char_space = char_width * (1/SPACE_FACTOR - 1);
	 /* fprintf(stderr,"SI h=%g\n",char_height); **EK*/
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant);
	    dumpit(1);
	    break;

	case 'L':		/* Character Slant */
	case 'l':
	    debugp((stderr,"%c%c",op1,op2));
	    if (SIGNED_NUMERIC)
		char_slant = char_height * getval();
	    else
		char_slant = 0;

	    char_space = char_width * (1/SPACE_FACTOR - 1);
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant);
	    dumpit(1);
	    break;

	case 'M':		/* Symbol Mode */
	case 'm':
	    if ((ch = getc(stream)) != EOF && ch != ';' && isgraph(ch) > 0)
	    {
		 symbol = ch;
		 debugp((stderr,"%c",ch));
		 SYMBOL = 1;
	    }
	    else
		SYMBOL = 0;
	    dumpit(1);
	    break;

	case 'P':		/* Pen Select */
	case 'p':
	    debugp((stderr,"%c%c",op1,op2));
	    linesize();
	    dumpit(1);
	    break;

	case 'R':		/* Relative Character Size */
	case 'r':
	    debugp((stderr,"%c%c",op1,op2));
	    {
		float	pwidth, pheight;

		if (SIGNED_NUMERIC)
		{
		    pwidth = getval() * SCALE;		/* Percent */
		    pheight = getval() * SCALE; 	/* Percent */
		} else
		{
		    pwidth = DEFWIDTH * 100 * SCALE;
		    pheight = DEFHEIGHT * 100 * SCALE;
		}
		if(LANDSCAPE) {
		    char_width = FONT_W_MULT *(ymax - ymin) 
					 * YSCALE *  pwidth / 100.0;
		    char_height = FONT_H_MULT *(xmax - xmin) 
					 * XSCALE *  pheight / 100.0;
		}
/* JAS: "Why don't these have FONT_*_MULT's below, multiplied in?" */
/*EK* yes, why indeed! fixed it! */
/* BUG: but perhaps there is a better way? */
		else {
		    char_width = FONT_W_MULT * (xmax - xmin)
					* XSCALE * pwidth / 100.0;
		    char_height = FONT_H_MULT * (ymax - ymin) 
					* YSCALE * pheight / 100.0;
		}
		char_space = char_width * (1/SPACE_FACTOR - 1);
	    }
	 /* fprintf(stderr,"SR h=%g\n", char_height); **EK*/
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant);
	    dumpit(1);
	    break;

	case 'S':		/* Select Standard Set */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'T':
    case 't':
	op2 = getc(stream);
	switch (op2)
	{
	case 'L':		/* Tick Length */
	case 'l':
				/* Feature added by Gordon Jacobs */
	    debugp((stderr,"%c%c",op1,op2));
	    if(SIGNED_NUMERIC) {
		tlp = 0.01 * getval();
		if(SIGNED_NUMERIC)
		    tln = 0.01 * getval();
		else
		    tln = 0.0;
	    }
	    else
		tlp = tln = 0.005;   /* defaults */
	    dumpit(1);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'U':
    case 'u':
	op2 = getc(stream);
	switch (op2)
	/*							    */
	/* This case has been modified by Gerald William Kokodyniak */
	/* at the University of Toronto, Department of Mechanical   */
	/* Engineering. It is presently operational with a calls    */
	/* made to a new subroutine/function called:		    */
	/*		 userdefchar()				    */
	/*							    */
	/*  Heavily modified by Gordon Jacobs. Size of user	    */
	/*  character now depends on regular character size.	    */
	/*  Orientation of character also depends on that of	    */
	/*  regular character set.				    */
	{
	case 'C':		/* User Defined Character */
	case 'c':
	    debugp((stderr,"%c%c",op1,op2));
	    userdefchar();
	    dumpit(1);
	    break;

	case 'F':		/* User-defined Fill Type */
	case 'f':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'V':
    case 'v':
	op2 = getc(stream);
	switch (op2)
	{
	case 'S':		/* Velocity Select */
	case 's':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'W':			/* Not HP-GL */
    case 'w':
	op2 = getc(stream);
	switch (op2)
	{
	case 'G':		/* Fill Wedge */
	case 'g':
	    notimp((stderr,"Not Implemented: %c%c",op1,op2));
	    dumpit(2);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown RD-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    case 'X':
    case 'x':
	op2 = getc(stream);
	switch (op2)
	{
	case 'T':		/* X Tick */
	case 't':
	    debugp((stderr,"%c%c",op1,op2));
	    tick(XTICK);	/* Tick() added by Gordon Jacobs */
	    dumpit(1);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command  ", op1, op2));
	    dumpit(2);
	}
	break;

    case 'Y':
    case 'y':
	op2 = getc(stream);
	switch (op2)
	{
	case 'T':		/* Y Tick */
	case 't':
	    debugp((stderr,"%c%c",op1,op2));
	    tick(YTICK);	/* Tick() added by Gordon Jacobs */
	    dumpit(1);
	    break;

	default:
	    notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2));
	    dumpit(2);
	}
	break;

    default:
	op2 = getc(stream);
	notimp((stderr, "Warning: %c%c Unknown HP-GL Command\n", op1,op2));
	dumpit(2);
	break;
    }
}

void dumpit(int x)
{
    /* Dump all characters until we get to another command letter.
     * This is to make sure that we have a clean start for the next command
     */
    while (((ch = getc(stream)) != EOF) && ch < 'A')
    {
	if (x == 1 ) { debugp((stderr,"%c",ch)); }
	if (x == 2 ) { notimp((stderr,"%c",ch)); }
    }
    if (x == 1 ) { debugp((stderr,"\n")); }
    if (x == 2 ) { notimp((stderr,"\n")); }
    ungetc(ch,stream);
}

void dumpcomma(void)
{
    /* Dump the possible comma after a plot command. */
    while (((ch = getc(stream)) != EOF) && ch == ',')
	debugp((stderr,"%c",ch));
    ungetc(ch,stream);
}
