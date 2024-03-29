#include "cube.h"

void    draw3dmap(double length, int x, player *pl, int wasvert, double xp, double yp)
{
    double toprojection;
    double wallheight;
    double vheight;
    double height;
    double y;       
    int i = 0;
    int color;

    wallheight = (double)(pl->map->h) / 20;
    color = -1;
    toprojection = (pl->map->w / 2) / tan(30 * M_PI / 180);
    
    vheight = (wallheight * toprojection) / (length);
    if (vheight >= pl->map->h)
        vheight = pl->map->h;
    y = (pl->map->h  - vheight) /  2;

    height = vheight;
    while (++color < y)
        put_pixel(pl->map, x, color, pl->map->txt->celling);
    while (vheight-- > 0)
    {
        color = handel_image_color(wasvert, xp, yp, pl, height, i);
        put_pixel(pl->map, x, y, color);
        i++;
        y++;
    }
    while (y < pl->map->h)
    {
        put_pixel(pl->map, x, y, pl->map->txt->floor);
        y++;
    }
}   