/*
 * This procedure translates RD-GL (Roland DG Graphic Language) into the
 * equivalent PostScript language. 
 *
 * The RD-GL is a superset equivalent to HP-GL 
 *
 * Don McCormick 
 */

#include "defn.h"

/* The folowing defaults should be 0.5% and 1.0% for the respective  character
 * width and height, however this is too small when scaled to Postcript
 * charcter sizes.
 */
float DEFWIDTH = 0.0075 ;	/* 0.75 % of P2x - P1x for default char width */
float DEFHEIGHT = 0.015 ;	/* 1.5 % of P2y - P1y for default char height */

/*
 * Note the 1.4 multiplier allows for an approx conversion
 * between the plotter char size and what would be expected
 * on the Laser printer.
 */
float PSmult = 1.4 ;

hpglcom(op1)
char    op1 ;
{
    char    op2 ;
    int     arg ;

    PSmult *= SCALE ;

    switch (op1)
    {
    case 'A':
    case 'a':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (AA) Arc Absolute */
	case 'a':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: Arc absolute not implemented yet\n") ;
	    break ;

	case 'P':		/* (AP) Automatic Pen Lift (not implemented) */
	case 'p':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    break ;

	case 'R':		/* (AR) Arc Relative */
	case 'r':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: Arc relative not implemented yet\n") ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n\n", op1, op2) ;
	}
	break ;

    case 'C':
    case 'c':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (CA) Alternate Character Set (Not Used) */
	case 'a':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: Alt character set not implemented yet\n") ;
	    break ;

	case 'I':		/* (CI) Circle */
	case 'i':
	    circle(RDGLCIRCLE) ;
	    break ;

	case 'P':		/* (CP) Character Plot */
	case 'p':
	    {
		float   xspace, yspace ;

		xspace = getval() * XSCALE * (char_width + char_space) ;
		yspace = getval() * YSCALE * (char_width + char_space) ;
		end_draw() ;
		printf("    %g mm %g mm %s\n", xspace, yspace, RMOVE) ;
	    }
	    break ;

	case 'S':		/* (CS) Standard Character Set */
	case 's':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'D':
    case 'd':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'C':		/* (DC) Digitize Clear (Not Used) */
	case 'c':
	    break ;

	case 'F':		/* (DF) Default */
	case 'f':
	    SETDOT = FALSE ;
	    PENDOWN = FALSE ;
	    SYMBOL = 0 ;
	    EOL = '\003' ;
	    char_angle = 0 ;
	    char_slant = 0 ;
	    char_width = DEFWIDTH * (P2x - P1x) * XSCALE * PSmult ;
	    char_height = DEFHEIGHT * (P2y - P1y) * YSCALE * PSmult ;
	    char_space = char_width * (1/.67 - 1) ;
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant) ;
	    break ;

	case 'I':		/* (DI) Absolute Direction */
	case 'i':
	    {
		float   run, rise ;

		if (SIGNED_NUMERIC)
		{
		    run = getval() * XSCALE ;
		    rise = getval() * YSCALE ;
		    char_angle = atan2(rise, run) / deg2rad ;
		}
		else
		    char_angle = 0 ;
	    }
	    break ;

	case 'P':		/* (DP) Digitize Point (Not Used) */
	case 'p':
	    break ;

	case 'R':		/* (DR) Relative Direction */
	case 'r':
	    {
		float   run, rise ;

		if (SIGNED_NUMERIC)
		{
		    run = getval() * XSCALE ;
		    rise = getval() * YSCALE ;
		    char_angle += atan2(rise, run) / deg2rad ;
		}
		else
		    char_angle = 0 ;
	    }
	    break ;

	case 'T':		/* (DT) Define Label Terminator */
	case 't':
	    if ((arg = getc(stream)) != EOF)
		EOL = arg ;	/* End of label terminator */
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'E':
    case 'e':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (EA) Edge Rectangle Absolute */
	case 'a':
	    break ;

	case 'R':		/* (ER) Edge Rectangle Relative */
	case 'r':
	    break ;

	case 'W':		/* (EW) Edge Wedge */
	case 'w':
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown RD-GL Command\n", op1, op2) ;
	}
	break ;

    case 'F':
    case 'f':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'T':		/* (FT) Fill Type */
	case 't':
	    fprintf(stderr, "Warning: Fill type not implemented yet\n") ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'I':
    case 'i':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'M':		/* (IM) Input Mask (Not Used) */
	case 'm':
	    break ;

	case 'N':		/* (IN) Initialize */
	case 'n':
	    defcoords() ;
	    SETDOT = FALSE ;
	    PENDOWN = FALSE ;
	    SYMBOL = 0 ;
	    EOL = '\003' ;
	    char_angle = 0 ;
	    char_slant = 0 ;
	    char_width = DEFWIDTH * (P2x - P1x) * XSCALE * PSmult ;
	    char_height = DEFHEIGHT * (P2y - P1y) * YSCALE * PSmult ;
	    char_space = char_width * (1/0.67 - 1) ;
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant) ;
	    break ;

	case 'P':		/* (IP) Input P1 and P2 */
	case 'p':
	    if (SIGNED_NUMERIC)
	    {
		P1x = getval() ;
	        if (SIGNED_NUMERIC)
		    P1y = getval() ;
		else
		{
		    fprintf(stderr,"Error expecting P1y from IP instruction\n") ;
		    defcoords() ;		/* Set default coordinates */
		    break ;
		}
	    }
	    else
	    {
		defcoords() ;		/* Set default coordinates */
		break ;
	    }

	    if (SIGNED_NUMERIC)
	    {
		P2x= getval() ;
	        if (SIGNED_NUMERIC)
		    P2y = getval() ;
		else
		{
		    fprintf(stderr,"Error expecting P2y from IP instruction\n") ;
		    defcoords() ;		/* Set default coordinates */
		    break ;
		}
	    }
	    else
	    {
		P2x += P1x ;			/* P2 tracks P1 */
		P2y += P1y ;			/* P2 tracks P1 */
	    }
	    viewport(0) ;
	    break ;

	case 'W':		/* (IW) Input Window */
	case 'w':
	    window() ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'L':
    case 'l':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'B':		/* (LB) Label */
	case 'b':
	    textps(TEXT) ;
	    break ;

	case 'T':		/* (LT) Line Type */
	case 't':
	    linetype(LINE_TYPE_SCALE) ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'O':
    case 'o':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (OA) Output Actual Position */
	case 'a':
	    break ;

	case 'C':		/* (OC) Output Commanded Position */
	case 'c':
	    break ;

	case 'D':		/* (OD) Output Digitise */
	case 'd':
	    break ;

	case 'E':		/* (OD) Output Error */
	case 'e':
	    break ;

	case 'P':		/* (OP) Output P1 and P2 */
	case 'p':
	    break ;

	case 'S':		/* (OS) Output Status */
	case 's':
	    break ;

	case 'W':		/* (OW) Output Window */
	case 'w':
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'P':
    case 'p':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (PA) Plot Absolute */
	case 'a':
	    PLOTABS = TRUE ;
	    if (SIGNED_NUMERIC)
		if (SETDOT || SYMBOL)
		    plotdot(MOVE) ;
		else if (PENDOWN)
		    plotps(DRAW) ;
		else
		    plotps(MOVE) ;
	    break ;

	case 'D':		/* (PD) Pen Down */
	case 'd':
	    PENDOWN = TRUE ;
	    if (SIGNED_NUMERIC)
		if (SETDOT || SYMBOL)
		    plotdot(MOVE) ;
		else if (PLOTABS)
		    plotps(DRAW) ;
		else 
		    plotps(RDRAW) ;
	    break ;

	case 'R':		/* (PR) Plot Relative */
	case 'r':
	    PLOTABS = FALSE ;
	    if (SIGNED_NUMERIC)
		if (SETDOT || SYMBOL)
		    plotdot(RMOVE) ;
		else if (PENDOWN)
		    plotps(RDRAW) ;
		else
		    plotps(RMOVE) ;
	    break ;

	case 'T':		/* (PT) Pen Thickness */
	case 't':
	    {
		float   linewidth ;

		linewidth = getval() * SCALE ;		/* In mm */
		printf("%g mm setlinewidth\n", linewidth) ;
	    }
	    break ;

	case 'U':		/* (PU) Pen Up */
	case 'u':
	    PENDOWN = FALSE ;
	    if (SIGNED_NUMERIC)
		if (SETDOT)
		    plotdot(MOVE) ;
		else if (PLOTABS)
		    plotps(MOVE) ;
		else
		    plotps(RMOVE) ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'R':
    case 'r':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (RA) Shade Rectange Absolute */
	case 'a':
	    break ;

	case 'R':		/* (RR) Shade Rectangle Relative */
	case 'r':
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown RD-GL Command\n", op1, op2) ;
	}
	break ;

    case 'S':
    case 's':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'A':		/* (SA) Select Alternate Set (Not Used) */
	case 'a':
	    break ;

	case 'C':		/* (SC) Scale */
	case 'c':
	    if (SIGNED_NUMERIC)
		U1x = getval() ;
	    else			/* Turn Scaling off */
	    {
		SCALING = FALSE ;
		break ;
	    }

	    if (SIGNED_NUMERIC)
		U2x = getval() ;
	    else
	    {
		fprintf(stderr,"Error expecting U2x from SC instruction\n") ;
		SCALING = FALSE ;
		defcoords() ;		/* Set up default conditions */
		break ;
	    }
	    if (SIGNED_NUMERIC)
		U1y = getval() ;
	    else
	    {
		fprintf(stderr,"Error expecting U1y from SC instruction\n") ;
		SCALING = FALSE ;
		defcoords() ;		/* Set up default conditions */
		break ;
	    }
	    if (SIGNED_NUMERIC)
	    {
		U2y = getval() ;
	        SCALING = TRUE ;
	    }
	    else
	    {
		fprintf(stderr,"Error expecting U2y from SC instruction\n") ;
		SCALING = FALSE ;
		defcoords() ;		/* Set up default conditions */
		break ;
	    }
	    viewport(0) ;
	    break ;

	case 'I':		/* (SI) Absolute Character Size */
	case 'i':
	    if (SIGNED_NUMERIC)
	    {
		char_width = getval() * 10 * PSmult ;	/* In mm */
		char_height = getval() * 10 * PSmult ;	/* In mm */
		char_width *= 11040 / maxXrange ; /* Scale to A4 paper */
		char_height *= 7721 / maxYrange ; /* Scale to A4 paper */
	    } else
	    {
		if (((arg = getc(stream)) == ' ;') || isalpha(arg) != 0)
		{
		    ungetc(arg, stream) ;
		    if (strcmp(PaperSize, "A4") == 0)
		    {
		        char_width = 1.87 * PSmult ;
		        char_height = 2.69 * PSmult ;
			char_width *= 11040 / maxXrange ;
			char_height *= 7721 / maxYrange ;
		    }
		    else
		    {
		        char_width = 2.85 * PSmult ;
		        char_height = 3.75 * PSmult ;
			char_width *= 11040 / maxXrange ; /* Scale to A4 paper */
			char_height *= 7721 / maxYrange ; /* Scale to A4 paper */
		    }
		}
	    }
	    char_space = char_width * (1/.67 - 1) ;
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant) ;
	    break ;

	case 'L':		/* (SL) Character Slant */
	case 'l':
	    if (SIGNED_NUMERIC)
		char_slant = char_height * getval() ;
	    else
		char_slant = 0 ;

	    char_space = char_width * (1/.67 - 1) ;
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant) ;
	    break ;

	case 'M':		/* (SM) Symbol Mode */
	case 'm':
	    if ((arg = getc(stream)) != EOF && arg != ' ;' && isgraph(arg) > 0)
	    {
		 symbol = arg ;
		 SYMBOL = 1 ;
	    }
	    else
		SYMBOL = 0 ;
	    break ;

	case 'P':		/* (SP) Pen Select */
	case 'p':
	    linesize() ;
	    break ;

	case 'R':		/* (SR) Relative Character Size */
	case 'r':
	    {
		float   pwidth, pheight ;

		if (SIGNED_NUMERIC)
		{
		    pwidth = getval() ;		/* Percent */
		    pheight = getval() ;	/* Percent */
		} else
		{
		    pwidth = DEFWIDTH * 100 ;
		    pheight = DEFHEIGHT * 100 ;
		}
		char_width = (P2x - P1x) * XSCALE * pwidth / 100.0 * PSmult ;
		char_height = (P2y - P1y) * YSCALE * pheight / 100.0 * PSmult ;
	        char_space = char_width * (1/.67 - 1) ;
		char_width *= 11040 / maxXrange ; /* Scale to A4 paper */
		char_height *= 7721 / maxYrange ; /* Scale to A4 paper */
	    }
	    printf("/%s %g %g %g DefFont\n",
		font, char_width, char_height, char_slant) ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'T':
    case 't':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'L':		/* (TL) Tick Length */
	case 'l':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: Tick length not implemented yet\n") ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'U':
    case 'u':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'C':		/* (UC) User Defined Character */
	case 'c':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: User defined character not implemented yet\n") ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'V':
    case 'v':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'S':		/* (VS) Velocity Select */
	case 's':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'W':
    case 'w':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'G':		/* (WS) Shade Wedge */
	case 'g':
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown RD-GL Command\n", op1, op2) ;
	}
	break ;

    case 'X':
    case 'x':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'T':		/* (XT) X Tick */
	case 't':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: X tick not implemented yet\n") ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    case 'Y':
    case 'y':
	op2 = getc(stream) ;
	switch (op2)
	{
	case 'T':		/* (YT) Y Tick */
	case 't':
	    while (((arg = getc(stream)) != EOF) && isalpha(arg) == 0) ;
	    ungetc(arg, stream) ;
	    fprintf(stderr, "Warning: Y tick not implemented yet\n") ;
	    break ;

	default:
	    fprintf(stderr, "Warning: %c%c Unknown HP-GL Command\n", op1, op2) ;
	}
	break ;

    default:
	fprintf(stderr, "Warning: %c Unknown HP-GL First Op Command\n", op1) ;
	break ;
    }
}
