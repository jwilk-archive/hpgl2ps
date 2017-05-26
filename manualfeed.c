/*
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
manualfeed(arg)
int     arg;
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
