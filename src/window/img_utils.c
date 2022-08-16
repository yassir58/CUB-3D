#include "../../includes/cub3d.h"


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_rect (t_img *data, int x, int y, int width, int height, int color)
{
	int i;
	int j;
	int clr;

	i = 0;
	j = 0;
	while (i < height)
	{
		while (j < width)
		{
			// if (i == 0 || j == 0 || (j == width) || (i == height))
			// 	clr = 0x00FF0000;
			// else
				clr = color;
				my_mlx_pixel_put (data , (x + j), (y + i), clr);
			j++;
		}
		j = 0;
		i++;
	}
}