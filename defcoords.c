/*
 *	Define Scaling plotting points.
 *		P1 (P1x, P1y),  P2 (P2x, P2y)
 *
 *	Define User Unit mapping points.
 *		U1 (U1x, U1y),  U2 (U2x, U2y)
 *
 *	Plotter PaperSize can be:
 *		"A3" ISO (297mm by 420mm)
 *		"A4" ISO (210mm by 297mm)
 *		"A"  ANSI (8.5" by 11")
 *		"B"  ANSI (11" by 17")
 *
 *	Maximum Plotting Range ( HPGL Plotter units) maxXrange, maxYrange
 *
 *		"A4" ISO 0-11040 by 0-7721 	(274.6mm by 192.1mm)
 *		"A3" ISO 0-16158 by 0-11040	(401.9mm by 274.6mm)
 *		"A"  ANSI 0-10365 by 0-7962	(10.15" by 7.8")
 *		"B"  ANSI 0-16640 by 0-10365	(16.3" by 10.15")
 *
 *      Note: will be scaled to fit on A4 LaserWriter paper.
 *
 *	Mode can be:	"HPGL" or "DXY"
 *
 * Don McCormick
 */

#include "defn.h"

defcoords()
{
    if (strcmp(Mode, "HPGL") == 0)
    {
	if (strcmp(PaperSize, "A3") == 0)	/* HP-GL ISO A3 420mm * 297mm */
	{
	    maxXrange = 16158;
	    maxYrange = 11040;
	    P2x = U2x = 15370;
	    P2y = U2y = 10602;
	    P1x = U1x = 170;
	    P1y = U1y = 602;
	}
	else					/* HP-GL ISO A4 297mm * 210mm */
	{
	    maxXrange = 11040;
	    maxYrange = 7721;
	    P2x = U2x = 10603;
	    P2y = U2y = 7721;
	    P1x = U1x = 603;
	    P1y = U1y = 521;
	}
    }
    else
    {
	if (strcmp(PaperSize, "A3") == 0)	/* DXY ISO A3 420mm * 297mm */
	{
	    maxXrange = P2x = U2x = 3800;
	    maxYrange = P2y = U2y = 2700;
	}
	else					/* DXY ISO A4 297mm * 210mm */
	{
	    maxXrange = P2x = U2x = 2700;
	    maxYrange = P2y = U2x = 1920;
	}
        P1x = P1y = U1x = U1y = 0.0;
    }
}
