/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:21:09 by yelatman          #+#    #+#             */
/*   Updated: 2022/10/16 10:50:13 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player_position(t_global_state *state)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (i < state->grid->row)
	{
		while (j < state->grid->col)
		{
			if (state->data->map[i][j] == state->data->player_direction)
				set_player_position (state, x, y);
			x += state->data->tile_x;
			j++;
		}
		j = 0;
		x = 0;
		y += state->data->tile_y ;
		i++;
	}
}

void	init_game(t_global_state *state)
{
	init_player_position (state);
	load_texture_images (state);
	set_colors (state);
}

void	load_texture_images(t_global_state *state)
{
	state->north_texture.img.img = mlx_xpm_file_to_image (state->vars->mlx,
			get_texture_path (state, "NO"), &state->north_texture.width,
			&state->north_texture.height);
	state->north_texture.img.addr = (int *)mlx_get_data_addr
		(state->north_texture.img.img,
			&(state->north_texture.img.bits_per_pixel),
			&(state->north_texture.img.line_length),
			&(state->north_texture.img.endian));
	state->south_texture.img.img = mlx_xpm_file_to_image (state->vars->mlx,
			get_texture_path (state, "SO"), &state->south_texture.width,
			&state->south_texture.height);
	state->south_texture.img.addr = (int *)mlx_get_data_addr
		(state->south_texture.img.img,
			&(state->south_texture.img.bits_per_pixel),
			&(state->south_texture.img.line_length),
			&(state->south_texture.img.endian));
	load_textures (state);
}

void	init_shoot_sprites(t_global_state *state)
{
	int		i;
	char	*path;
	char	*tmp;
	char	*indx;

	i = 0;
	path = NULL;
	state->sprites = malloc (sizeof (t_texture) * 7);
	while (i < 7)
	{
		indx = ft_itoa(i + 1);
		tmp = ft_strjoin ("frames/fr", indx);
		path = ft_strjoin (tmp, ".xpm");
		state->sprites[i].img.img = mlx_xpm_file_to_image (state->vars->mlx,
				path, &state->sprites[i].width, &state->sprites[i].height);
		state->sprites[i].img.addr = (int *)mlx_get_data_addr
			(state->sprites[i].img.img,
				&state->sprites[i].img.bits_per_pixel,
				&state->sprites[i].img.line_length,
				&state->sprites[i].img.endian);
		free (path);
		free (tmp);
		free (indx);
		i++;
	}
}

void	init_releaod_sprites(t_global_state *state)
{
	int		i;
	char	*path;
	char	*tmp;
	char	*indx;

	i = 0;
	state->releaod_sprites = malloc (sizeof (t_texture) * 10);
	while (i < 10)
	{
		indx = ft_itoa(8 + i);
		tmp = ft_strjoin ("frames/fr", indx);
		path = ft_strjoin (tmp, ".xpm");
		state->releaod_sprites[i].img.img = mlx_xpm_file_to_image
			(state->vars->mlx, path,
				&state->releaod_sprites[i].width,
				&state->releaod_sprites[i].height);
		state->releaod_sprites[i].img.addr = (int *)mlx_get_data_addr
			(state->releaod_sprites[i].img.img,
				&state->releaod_sprites[i].img.bits_per_pixel,
				&state->releaod_sprites[i].img.line_length,
				&state->releaod_sprites[i].img.endian);
		free_vars (path, tmp, indx);
		i++;
	}
}
