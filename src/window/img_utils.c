#include "../../includes/cub3d.h"


void	my_mlx_pixel_put(t_global_state *state, int x, int y, int color, t_img *img)
{
	t_img *data;

	if (img == NULL)
		data = &state->img;
	else
		data = img;
	if ((x >= 0 && x < state->data->window_width) && (y >= 0 && y < state->data->window_height))
		data->addr[(state->data->window_width * y) + x] = color;
}


void draw_rect (int x, int y, int color, t_global_state *state)
{
	int i;
	int j;
	int clr;

	i = 0;
	j = 0;
	clr = 0;
	while (i <= MINIMAP_CEL)
	{
		while (j <= MINIMAP_CEL)
		{
			if (i == 0 || j == 0 || (j == MINIMAP_CEL) || (i == MINIMAP_CEL))
				clr = 0x008ACB88;
			else
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
	int start;
	int end;
	int texelClr;

	start = y;
	end = colHeight;
	while (end--)
	{
		txtOffsetY = (start - y) * (state->current.height / colHeight);
		texelClr = state->current.img.addr[(state->current.width * txtOffsetY) + txtOffsetX];
		my_mlx_pixel_put (state , x, start, texelClr, &testing_img);
		start++;
	}
	(void)color;
}

void draw_player (int color, t_global_state *state)
{
	double i, angle, x1, y1, j;
	// int x_2;
	// int y_2;
	// double ang;

	i = 0.0, angle = 0.0, x1 = 0.0, y1 = 0.0 , j = 0.0;

	state->player->d_x = (MINIMAP_RES / 2);
	state->player->d_y = (MINIMAP_RES / 2);
	while (j <= state->player->radius)
	{
		while (i < 360)
		{
			angle  =  i;
			x1 = j * cos(angle * (M_PI / 180));
			y1 = j * sin (angle * (M_PI / 180));
			my_mlx_pixel_put (state , ((MINIMAP_RES / 2) + x1), ((MINIMAP_RES / 2) + y1), color, NULL);
			i += 0.1;
		}
		i = 0;
		j += 0.1;
	}
	// printf ("|x = %d|y = %d|\n", state->player->d_x, state->player->d_y);
	draw_line (state->player->d_x, state->player->d_y, state);
}