/*
 * Returns a real number 
 */

#include "defn.h"

#define ERROR "Two or more decimal places in a number"

float
getval()
{
    char    valbuf[10];
    float   value;
    int     DECIMAL = 0;
    int     i;

    /* Null the value buffer "valbuf" */
    for (i = 0; i < 10; i++)
	valbuf[i] = NULL;

    i = 0;
    ch = getc(stream);

/*
 * Get Rid of seperators
 */
    while ((ch == ' ') || (ch == ','))
	ch = getc(stream);

    while ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-' || ch == '+')
    {
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
    ungetc(ch, stream);		/* Put non numeric char back */
    value = atof (valbuf);
    return (value);
}
