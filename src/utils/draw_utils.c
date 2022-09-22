#include "../../includes/cub3d.h"


void draw_minimap (t_global_state *state)
{
    int player_x;
    int player_y;
    int j = 0;
    int y = 0;
    int indx_x;
    int indx_y;

    player_x = position_in_map (state->player->initx, state);
    player_y = position_in_map (state->player->inity, state);
    indx_x = player_x - ((MINIMAP_ROW / 2));
    indx_y = player_y - (MINIMAP_ROW / 2);
    while (j < MINIMAP_ROW)
    {
        if ((indx_y + j >= 0 && indx_y + j < state->grid->row))
            draw_minimap_row (player_x, player_y, y, state, indx_x, indx_y + j);
        else
            draw_minimap_wall (y, state, indx_x);
        y += MINIMAP_CEL;
        j++;
    }
}

void render_minimap_cel (int x, int y, t_global_state *state, int elm)
{
    if (elm == 'p')
    draw_minirect (x, y, 0x00FF0156, state);
    else if (elm == '0' ||elm == ' ' || elm =='N' || 
        elm == 'S' || elm == 'W' || elm == 'E')
    draw_minirect (x, y, 0x00000000, state);
    else
    draw_minirect (x, y, 0x00FFF80A, state);
}


void draw_minimap_row (int player_x, int player_y,int y, t_global_state *state, int indx_x , int indx_y)
{
    int i;
    int x;

    i = 0;
    x = 0;
    while (i < MINIMAP_ROW)
    {
        if (indx_x + i == player_x && indx_y == player_y)
            render_minimap_cel (x, y,state, 'p');
        else if ((indx_x + i >= 0 && indx_x + i <= state->grid->col))
            render_minimap_cel (x, y, state, state->data->map[indx_y][indx_x + i]);
        else 
            render_minimap_cel (x, y, state, ' ');
            x += MINIMAP_CEL;
        i++;
    }
}

void draw_minimap_wall (int y, t_global_state *state, int indx_x)
{
    int i;
    int x;

    i = 0;
    x = 0;
    while (i < MINIMAP_ROW)
    {
        if ((indx_x + i >= 0 && indx_x + i < state->grid->col))
            render_minimap_cel (x, y, state, '0');
        else
            draw_minirect (x, y, 0x00000000, state);
        x += MINIMAP_CEL;
        i++;
    }
}