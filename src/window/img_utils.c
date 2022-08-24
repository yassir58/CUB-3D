#include "../../includes/cub3d.h"


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_rect (int x, int y, int color)
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
			if (i == 0 || j == 0 || (j == TILE_SIZE) || (i == TILE_SIZE))
				clr = 0x00FF0000;
			else
				clr = color;
			my_mlx_pixel_put ((&g_data.img) , (x + j), (y + i), clr);
			j++;
		}
		j = 0;
		i++;
	}
}

void draw_player (int color)
{
	double i, angle, x1, y1, j;

	i = 0.0, angle = 0.0, x1 = 0.0, y1 = 0.0 , j = 0.0;

	g_data.player.deriction_arrow_x = g_data.player.initx;
	g_data.player.deriction_arrow_y = g_data.player.inity;
	while (j <= g_data.player.radius)
	{
		while (i < 360)
		{
			angle  =  i;
			x1 = j * cos(angle * (M_PI / 180));
			y1 = j * sin (angle * (M_PI / 180));
			my_mlx_pixel_put ((&g_data.img) , (g_data.player.initx + x1), (g_data.player.inity + y1), color);
			i += 0.1;
		}
		i = 0;
		j += 0.1;
	}
	 draw_line (g_data.player.deriction_arrow_x, g_data.player.deriction_arrow_y, g_data.player.deriction_arrow_x + 100, g_data.player.deriction_arrow_y + 200);
}