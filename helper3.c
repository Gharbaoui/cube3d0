#include "cube.h"

void    handel_rest_pos_sprite(player *pl, int j, double x, double y, int lineindex)
{
    char **str;
    char *line;
     str = pl->map->map_lines;
     while (str[lineindex])
     {
         line = str[lineindex];
         while (*line)
         {
             if (*line == '2')
             {
                 pl->map->obj[++j]->x = x + (pl->map->width / 2);
                 pl->map->obj[j]->y = y + (pl->map->height / 2);
                 pl->map->obj[j]->hit = 0;
             }
             else
                x += pl->map->width;
            line++;
         }
         x = 0;
         y += pl->map->height;
         lineindex++;
     }
     pl->map->obj[++j]->x = -1;
     pl->map->obj[j]->y = -1;
}

void      handel_slope(double x0, double y0, double x1, double y1, sprite **sp, double length)
{
    double slope1, slope2, b1, b2;
    double y, xinter, yinter, x;
    double length1, length2;
    int j;

    j = -1;
    if(x1 != x0)
    {
        while ((y = sp[++j]->y) >= 0 && (x = sp[j]->x) >= 0)
        {
            slope1 = (y1 - y0) / (x1 - x0);
            b1 = y0 - (slope1 * x0);
            slope2 = -1 / slope1;
            b2 = y - (slope2 * x);
            xinter = (b1 - b2) / (slope2 - slope1);
            yinter = (slope1 * xinter) + b1;
            length1 = calculate_length(x0, y0, x1, y1);
            length2 = calculate_length(x0, y0, xinter, yinter);
            if (length2 < length1)
            {
                sp[j]->hit = 1;

            }
            else
            {
                sp[j]->hit = 0;           
            }
        }
    }
}

int     is_on_line(double slope, double x0, double y0, double x, double y)
{
    double check;
    check = (slope * x) + (y0 - (slope * x0));
    if (check == y)
        return 1;
    else 
        return 0;
}
