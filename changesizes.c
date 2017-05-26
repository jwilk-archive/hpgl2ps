/*
 * This utility will take a string of real numbers seperated by commas and
 * put them in an array. 
 *
 * Don McCormick 
 */
#include "defn.h"

#define ERROR1 "Only 9 line sizes allowed"
#define ERROR2 "Too many decimal points in number"
#define ERROR3 "line size specification incorrect"
#define ERROR4 "Max no of characters for each line size is 5"

changesizes(sizebuf)
char    sizebuf[50];
{
    int     i;
    int     j = 0;
    int     k = 0;
    int     DECIMAL = 0;
    float   number;
    char    numbuf[5];

    for (i = 0; i < 50; i++)
    {
	if (sizebuf[i] == ',' || sizebuf[i] == NULL)
	{
	    if ((number = atof(numbuf)) >= 0.01 && number <= 10)
		pen_size[j] = number;	/* Put number in array */
	    else
		fprintf(stderr, "Warning: line size too large ignored \n");

	    if (sizebuf[i] == NULL) return;

	    if (j++ > 8)
	    {
		fprintf(stderr, "Error: %s\n", ERROR1);
		exit(1);
	    }
	    for (k = 0; k < 5; k++)
		numbuf[k] = NULL;	/* Clear number buffer */

	    k = 0;
	    DECIMAL = 0;	/* One decimal per number */

	    while (sizebuf[i + 1] == ',' && sizebuf[i + 1] != NULL)
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
