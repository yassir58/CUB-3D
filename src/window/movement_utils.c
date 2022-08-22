#include "../../includes/cub3d.h"

int check_for_wall (int x, int y, int flag)
{
    int indx_x, indx_y;

    if (flag == DOWN)
    {
        indx_x = position_in_map (x);
        indx_y = position_in_map ((y + g_data.player.radius));
        printf ("OP:DOWN ==> char |%c|\n", g_data.data.map[indx_y][indx_x]);
    }
    else if (flag == UP)
    {
        indx_x = position_in_map (x);
        indx_y = position_in_map ((y - g_data.player.radius));
        printf ("OP:UP ==> char |%c|\n", g_data.data.map[indx_y][indx_x]);
    }
    else if (flag == LEFT)
    {
        indx_x = position_in_map ((x - g_data.player.radius));
        indx_y = position_in_map (y);
        printf ("OP:LEFT ==> char |%c|\n", g_data.data.map[indx_y][indx_x]);
    }
    else if (flag == RIGHT)
    {
        indx_x = position_in_map ((x + g_data.player.radius));
        indx_y = position_in_map (y);
        printf ("OP:RIGHT ==> char |%c|\n", g_data.data.map[indx_y][indx_x]);
    }
    return (0);
}



int position_in_map (int cord)
{
    int n;

    n = cord/TILE_SIZE;
    return (n);
}


void get_player_position (int *row, int *col)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (g_data.data.map[i])
    {
        while (g_data.data.map[i][j])
        {
            if (g_data.data.map [i][j] == 'P')
            {
                *row = i;
                *col = j;
                break;
            }
            j++;
        }
        j = 0;
        i++;
    }
}