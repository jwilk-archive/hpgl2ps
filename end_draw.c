#include "defn.h"

end_draw()
{
    if (DRAW_FLAG)
    {
	if (lastXmove == absX && lastYmove == absY)
	    printf("closepath\n");

	printf("stroke\n");
	DRAW_FLAG = 0;
    }
    dcount = 0;
}
