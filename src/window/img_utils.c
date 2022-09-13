#include "../../includes/cub3d.h"


void	my_mlx_pixel_put(t_global_state *state, int x, int y, int color, t_img *img)
{
	t_img *data;
	char	*dst;

	if (img == NULL)
		data = &state->img;
	else
		data = img;
	if ((x >= 0 && x < state->data->window_width) && (y >= 0 && y < state->data->window_height))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}



unsigned int get_pixel_color (int x, int y, t_img *img)
{
	t_img *data;
	char *dst;

	data = img;
	dst = NULL;
	if ((x >= 0 && x < w) && (y >= 0 && y < h))
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	else 
		return (0);
	return (*(unsigned int*)dst);
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
			clr = color;
			my_mlx_pixel_put (state , (x + j), (y + i), clr, NULL);
			j++;
		}
		j = 0;
		i++;
	}
}

void draw_column (int x, int y, int color, t_global_state *state, double colHeight)
{
	int i;
	int j;
	int clr;
	int texelClr = 0;

	i = 0;
	j = 0;
	clr = 0;
	while (i < colHeight)
	{
		while (j < RAY_THICKNESS)
		{
			clr = color;
			txtOffsetY = i * (TILE_SIZE / colHeight);
			texelClr = get_pixel_color (txtOffsetX, txtOffsetY, &texture_img);
			// printf ("|txl clr %d x %d y %d \n|", texelClr, txtOffsetX, txtOffsetY);
			my_mlx_pixel_put (state , (x + j), (y + i), texelClr, &testing_img);
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
			my_mlx_pixel_put (state , (state->player->initx + x1), (state->player->inity + y1), color, NULL);
			i += 0.1;
		}
		i = 0;
		j += 0.1;
	}
	// printf ("|x = %d|y = %d|\n", state->player->d_x, state->player->d_y);
	draw_line (state->player->d_x, state->player->d_y, state);
}