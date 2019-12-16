#include "cube.h"

double raycasting(player *pl, double angel, double *xp, double *yp, int *wasvert)
{
    dirction dir;
    double length_h;
    double length_v;
    int max =  2147483647;
    double ypos;
    double dx;

    angel = handel_angel(angel);
    ray_dirction(&dir, angel);
    handel_ypos_dx(&ypos, &dx, pl, dir);
    length_h = (!(dir.strightright || dir.strightleft)) ? handel_h(dx, ypos, pl, &dir) : (double)max;
    length_v = handel_raycasting_vert(pl, &dir);
    if (length_h > length_v)
    {
        *wasvert = 1;
        *xp = dir.xv;
        *yp = dir.yv;
    }
    else
    {
        *wasvert = 0;
        *xp = dir.xh;
        *yp = dir.yh;
    }
    return ((length_h > length_v) ? length_v : length_h);
}

double      handel_raycasting_vert(player *pl, dirction *dir)
{
    double length;
    double xpos;
    double dy;
    int maxint = 2147483647;

    xpos = (int)pl->x - ((int)pl->x % pl->map->width);
    xpos += (dir->right || dir->strightright) ? pl->map->width : 0;
    dy = (!dir->strightup && !dir->strightdown) ? (pl->x - xpos) * tan(dir->angel * M_PI / 180) : 0;
    dy *= ((dir->up && dy > 0) || (dir->down && dy < 0)) ? -1 : 1;
    xpos -= (dir->left || dir->strightleft) ? 1 : 0;
    length = (!dir->strightup && !dir->strightdown) ? handel_v(xpos, dy, pl, dir) : (double)maxint;
    return (length);
}

double handel_h(double dx, double ypos, player *pl, dirction *dir)
{
    double deltax;
    double deltay;
    double hx;
    double hy;
    int max;
    int horzhit;

    hx = hy = horzhit = 0;
    max = 2147483647;
    while ((pl->x + dx > 0 && pl->x + dx < pl->map->w) && (ypos > 0 && ypos < pl->map->h))
    {
        if (is_there_wall(pl->map, pl->x + dx, ypos))
        {
            horzhit = 1;
            dir->wasvert = 0;
            hx = pl->x + dx;
            hy = ypos;
            break ;
        }
        deltay = pl->map->height;
        deltay *= (dir->up || dir->strightup) ? -1 : 1;
        ypos += deltay;
        deltax = (!dir->spech) ? deltay / tan(dir->angel * M_PI / 180) : 0;
        deltax *= (((dir->right || dir->strightright) && deltax < 0) || ((dir->strightleft || dir->left) && deltax > 0)) ? -1 : 1;
        dx += deltax;
    }
    hy += (dir->up || dir->strightup) ? 1 : 0;
    if (horzhit)
    {
        dir->xh = hx;
        dir->yh = hy;
    }
    return ((horzhit) ? calculate_length(pl->x, pl->y, hx, hy) : (double)max);
}

double handel_v(double xpos, double dy, player *pl, dirction *dir)
{
    double vx;
    double vy;
    double deltax;
    double deltay;
    int maxint = 2147483647;

    while ((xpos > 0 && xpos < pl->map->w) && (pl->y + dy > 0 && pl->y + dy < pl->map->map_heigth * pl->map->height))
    {
        if (is_there_wall(pl->map, xpos, pl->y + dy))
        {
            dir->wasvert = 1;
            vx = xpos;
            vy = pl->y + dy;
            break ;
        }
        deltax = pl->map->width;
        deltax *= (dir->left || dir->strightleft) ? -1 : 1;
        deltay = (deltax) * tan(dir->angel * M_PI / 180);
        deltay *= ((dir->up && deltay > 0) || (dir->down && deltay < 0)) ? -1 : 1;
        xpos += deltax;
        dy += deltay;
    }
    vx += (dir->left || dir->strightleft) ? 1 : 0;
    if (dir->wasvert)
    {
        dir->xv = vx;
        dir->yv = vy;
    }
    return ((dir->wasvert) ? calculate_length(pl->x, pl->y, vx, vy) : (double)maxint);
}
