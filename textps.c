#include "defn.h"

#define MAXBUFSIZE 100

textps(type)
int     type;
{
    int     chr;
    char    buffer[MAXBUFSIZE];
    int	    intval;
    int     i;

    end_draw();

    if (type == TEXT)
    {
	for (i = 0 ; i < MAXBUFSIZE; i++)	/* Clear buffer */
	    buffer[i] = NULL;

	i = 0;					/* Reset buffer counter */

/*
 * For a mono spaced font (Emulates the plotter)
 */
	while (((chr = getc(stream)) != EOF)
			&& chr != CR && chr != LF && chr != EOL)
	{
	    buffer[i++] = chr;
	    if (chr == '(' || chr == ')')
	        printf("%g %g 1 %g (\\%c) Text\n", absX, absY, char_angle, chr);
	    else
	        printf("%g %g 1 %g (%c) Text\n", absX, absY, char_angle, chr);
 	    absX += (char_width) * cos(char_angle * deg2rad);
 	    absY += (char_width) * sin(char_angle * deg2rad);
	}
    }
    else			/* Must be a MARK */
    {
	int     symb_num;
	char    *symbol;

	if (SIGNED_NUMERIC)
	    symb_num = getval();
	else
	{
	    fprintf(stderr,
		    "Error: expecting a symbol number not %c (%d)",
		    symb_num, symb_num);
	    exit(1);
	}
	intval = (int)(getval() + 0.5);
	switch (intval)
	{
	case 0:
	    strcpy(symbol, "*");
	    break;

	case 1:
	    strcpy(symbol, "+");
	    break;

	case 2:
	    strcpy(symbol, "#");
	    break;

	case 3:
	    strcpy(symbol, "@");
	    break;

	case 4:
	    strcpy(symbol, "%");
	    break;

	case 5:
	    strcpy(symbol, "|");
	    break;

	case 6:
	    strcpy(symbol, "=");
	    break;

	case 7:
	    strcpy(symbol, "&");
	    break;

	case 9:
	    strcpy(symbol, "O");
	    break;

	case 10:
	    strcpy(symbol, "0");
	    break;

	case 11:
	    strcpy(symbol, "Y");
	    break;

	case 12:
	    strcpy(symbol, "X");
	    break;

	case 13:
	    strcpy(symbol, "Z");
	    break;

	case 14:
	    strcpy(symbol, "S");
	    break;

	case 15:
	    strcpy(symbol, "Q");
	    break;

	default:
	    fprintf(stderr, "Warning symbol number is %d\n", symb_num);
	    strcpy(symbol, "*");
	    break;
	}
	printf("%g %g 5 %g (%s) Text\n", absX, absY, char_angle, symbol);
    }
}
