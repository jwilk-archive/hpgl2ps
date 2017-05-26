#include    "defn.h"

#define USAGE "Usage: hpgl2ps [-amr] [-l line sizes] [-s scale] [-x offset] [-y offset] [file]\n"

main(argc, argv)
int     argc ;
char   *argv[] ;
{
    extern int optind ;
    extern char *optarg ;

    int     op ;
    int     opt ;
    int	    MANUAL_FEED = 0 ;			/* DEFAULT: No manual feed */

    DEBUG = FALSE ;
    SCALING = FALSE ;
    PaperSize = "A3" ;
    Mode = "HPGL" ;
    defcoords() ;

    plotinit() ;			/* Get other initialiasations */

    while ((opt = getopt(argc, argv, "Dal:ms:x:y:r")) != EOF)
    {
	switch (opt)
	{
	case 'D':
	    DEBUG = TRUE ;
	    break ;

	case 'a':		/* HP-GL ISO A4 297mm * 210mm */
	    PaperSize = "A4" ;
	    defcoords() ;
	    break ;

	case 'l':
	    changesizes(optarg) ;
	    break ;

	case 'm':
	    MANUAL_FEED = 1 ;
	    break ;

	case 'r':
	    LANDSCAPE = FALSE ;
	    break ;

	case 's':
	    SCALE = atof(optarg) ;
	    if (SCALE < 0.1)
		SCALE = 0.1 ;
	    else
	    if (SCALE > 3)
		SCALE = 3 ;
	    break ;

	case 'x':
	    xoffset = atof(optarg) ;
	    break ;

	case 'y':
	    yoffset = atof(optarg) ;
	    break ;

	default:
	    fprintf(stderr, "%s\n", USAGE) ;
	    exit(1) ;
	}
    }
    if (optind == argc)
	stream = stdin ;
    else if ((stream = fopen(argv[optind], "r")) == NULL)
    {
	fprintf(stderr, "ERROR: cannot open \"%s\"\n", argv[optind]) ;
	exit(1) ;
    }
    ps_macros() ;			/* Output PostScript Macros */

    viewport(1) ;			/* Scale the viewport for the plot */

    if (MANUAL_FEED)
	manualfeed(1) ;

    while ((op = getc(stream)) != EOF)
	if (isalpha(op) > 0)
	    hpglcom(op) ;

    end_draw() ;

    printf("showpage\n") ;

    if (MANUAL_FEED)
	manualfeed(0) ;
}
