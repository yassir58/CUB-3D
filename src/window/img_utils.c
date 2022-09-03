#include "../../includes/cub3d.h"


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_rect (int x, int y, int color, t_global_state *state)
{
	int i;
	int j;
	int clr;

	i = 0;
	j = 0;
	clr = 0;
	while (i < TILE_SIZE)
	{
		while (j < TILE_SIZE)
		{
			// if (i == 0 || j == 0 || (j == TILE_SIZE) || (i == TILE_SIZE))
			// 	clr = 0x00FF0000;
			// else
				clr = color;
			my_mlx_pixel_put ((&state->img) , (x + j), (y + i), clr);
			j++;
		}
		j = 0;
		i++;
	}
}

void draw_player (int color, t_global_state *state)
{
	double i, angle, x1, y1, j;
	// int x_2;
	// int y_2;
	// double ang;

	i = 0.0, angle = 0.0, x1 = 0.0, y1 = 0.0 , j = 0.0;

	state->player->d_x = state->player->initx;
	state->player->d_y = state->player->inity;
	while (j <= state->player->radius)
	{
		while (i < 360)
		{
			angle  =  i;
			x1 = j * cos(angle * (M_PI / 180));
			y1 = j * sin (angle * (M_PI / 180));
			my_mlx_pixel_put ((&state->img) , (state->player->initx + x1), (state->player->inity + y1), color);
			i += 0.1;
		}
		i = 0;
		j += 0.1;
	}
	printf ("|x = %d|y = %d|\n", state->player->d_x, state->player->d_y);
	draw_line (state->player->d_x, state->player->d_y, state);
}