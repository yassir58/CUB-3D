#include "../../includes/cub3d.h"

int check_for_wall (int x, int y)
{
    int indx_x, indx_y;
    char c;

    c = 0;
    indx_x = next_vertical_position (x);
    indx_y = next_horizontal_position (y);
    c = g_data.data.map[indx_y][indx_x];
    return (c);
}

int next_vertical_position (int x)
{
    int n;

    n = x/TILE_SIZE;
    return (n);
}

int next_horizontal_position (int y)
{
    int n;

    n = y/TILE_SIZE;
    return (n);
}