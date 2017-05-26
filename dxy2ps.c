/* dxy2ps.c */

#include <stdio.h>
#include "dxycom.c"

#include <getopt.h>

#define USAGE "Usage: dxy2ps [-afmrv] [-f default_ps_font_name] [-l line sizes] [-s scale] [-x offset] [-y offset] [file]\nSee man page for more help.\n"

void main(int argc, char *argv[])
{
    extern int optind;
    extern char *optarg;

    int     ch; 				/* GWKMOD */
    int     op; 				/* GWKMOD */
    /* GWK: char    op; */
    int     MANUAL_FEED = 0;			/* DEFAULT: No manual feed */

    PaperSize = "A3";
    Mode = "DXY";
    plotcoords();			/* Set up plotter coordinates */

    plotinit(); 		/* Get other initialisations */

    while ((ch = getopt(argc, argv, "af:l:ms:x:y:r")) != EOF)
    {
	switch (ch)
	{
	case 'a':		/* DXY ISO A4 297mm * 210mm */
	    PaperSize = "A4";
	    plotcoords();
	    break;

	case 'f':
	    (void)sprintf(font, optarg);
	    break;

	case 'l':
	    changesizes(optarg);
	    break;

	case 'm':
	    MANUAL_FEED = 1;
	    break;

	case 'r':
	    LANDSCAPE = 0;
	    break;

	case 's':
	    SCALE = atof(optarg);
	    if (SCALE < 0.1)
		SCALE = 0.1;
	    else
	    if (SCALE > 3)
		SCALE = 3;
	    break;

	case 'v':
	    fprintf(stderr, "dxy2ps %s\n", VERSION);
	    exit(0);

	case 'x':
	    xoffset = atof(optarg);
	    break;

	case 'y':
	    yoffset = atof(optarg);
	    break;

	default:
	    fprintf(stderr, "%s\n", USAGE);
	    exit(1);
	}
    }
    if (optind == argc)
	stream = stdin;
    else if ((stream = fopen(argv[optind], "r")) == NULL)
    {
	fprintf(stderr, "ERROR: cannot open \"%s\"\n", argv[optind]);
	exit(1);
    }
    ps_macros();			/* Output PostScript Macros */

    viewport(); 	/* Scale the viewport for the plot */

    printf("/%s %g Font\n", font, char_height);

    if (MANUAL_FEED)
	manualfeed(1);

    while ((op = getc(stream)) != EOF)
	if ((isalpha(op) > 0) || op == '^')
	    dxycom(op);

    end_draw();

    printf("showpage\n");

    if (MANUAL_FEED)
	manualfeed(0);
    exit(0);
}
