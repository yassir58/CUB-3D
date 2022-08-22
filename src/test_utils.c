#include "../includes/cub3d.h"


void calculate_grid (t_map_list *list, int *col, int *row)
{
 
    t_map_list *temp;

    temp = list;
    *col = ft_strlen (temp->column) - 1;
    *row = 0;
    while (temp)
    {
        (*row)++;
        temp = temp->next;
    }
}


void draw_grid (void)
{
    int x, y ,i ,j;

    x = 0, y = 0, i = 0, j = 0;
   
    while (i < g_data.grid.row)
    {
        draw_row (i, &j , &x, y);
        j = 0;
        x = 0;
        y += TILE_SIZE;
        i++;
    }
}


void draw_row (int i, int *j, int *x, int y)
{
    while (*j < g_data.grid.col)
    {  
        if (g_data.data.map[i][*j] == '1')
            draw_rect (*x, y, WALL_CLR);
        else if (g_data.data.map[i][*j] == 'P')
        {
            draw_rect (*x, y, SPACE_CLR);
            if (g_data.player.initx == 0 && g_data.player.inity == 0)
            {
                g_data.player.initx = *x;
                g_data.player.inity = y;
            }
            draw_player (0x00FF0000);
        }
        else
            draw_rect (*x, y, SPACE_CLR);
        *x += TILE_SIZE;
        (*j)++;
    }
    // draw_line (100, 100, 200, 200);
}