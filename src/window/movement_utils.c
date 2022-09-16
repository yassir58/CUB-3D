#include "../../includes/cub3d.h"

int check_for_wall (int x, int y, t_global_state *state)
{
    int indx_x, indx_y;

    
    indx_x = position_in_map (x, state);
    indx_y = position_in_map (y, state);
    if (state->data->map[indx_y][indx_x] != '1')
        return (1);
    return (0);
}

int position_in_map (int cord, t_global_state *state)
{
    int n;

    n = cord/state->data->tileX;;
    return (n);
}


void get_player_position (int *row, int *col, t_global_state *state)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (state->data->map[i])
    {
        while (state->data->map[i][j])
        {
            if (state->data->map [i][j] == 'P')
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