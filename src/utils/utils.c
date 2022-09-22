#include "../../includes/cub3d.h"

double deg_to_radian (int deg)
{
    return (deg * (M_PI / 180));
}

int radian_to_deg(double rad)
{
    return ((rad / M_PI) * 180);
}

void calculate_grid (char **map, int *col, int *row)
{
   
   int i;
   int tmp;

    i = 0;
    tmp = 0;
    *col = 0;
    *row = 0;
    while (map[i])
    {
        tmp = ft_strlen (map[i]) - 1;
        if (tmp > *col)
            *col = tmp;
        (*row)++;
        i++;
    }
}

void get_rotation_cords (int *x_2, int *y_2, double angle, t_global_state *state)
{
    *x_2 = *x_2 + (cos (angle)  *  state->player->d_length);
    *y_2 = *y_2 + (sin (angle)  *  state->player->d_length);
}



void color (t_global_state *state, int color, int start)
{
    int i;
    int j;
    int max;

    i = start;
    j = 0;
    max = state->data->window_height;
    if (start == 0)
        max = state->data->window_height / 2;
    while (i < max)
    {
        while (j < state->data->window_width)
        {
            my_mlx_pixel_put (state, j, i, color, NULL);
            j++;
        }
        j = 0;
        i++;
    }
}