#include "cube.h"

void    handel_sprite(double length, player *pl, double x1, double y1, int *pcounter)
{
    double x0, y0, y, x, xinter, yinter;
    double slope1, slope2, b1, b2;
    double lengths;
    int index;
    sprite **sp;
    sprite obj;

    sp = pl->map->obj;
    obj = *(sp[0]);
    y = obj.y;
    x = obj.x;
    if (x0 != x1)
    {
        slope1 = (y1 - y0) / (x1 - x0);
        b1 = y0 -(slope1 * x0);
        slope2 = (slope1 != 0) ? (-1 / slope1) : 0;
        b2 = y - (slope2 * x);
        xinter = (b1 - b2) / (slope2 - slope1);
        yinter = (slope1 * xinter) + b1;
        lengths = calculate_length(x0, y0, xinter, yinter);
        if (lengths < length)
        {
            obj.hit = 1;
            *pcounter++;
            index = *pcounter - 1;
            obj.hitpoints[index].x = xinter;
            obj.hitpoints[index].y = yinter;
        }
        else
            obj.hit = 0;
    }
}
