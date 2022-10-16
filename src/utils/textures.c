/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:37:35 by yelatman          #+#    #+#             */
/*   Updated: 2022/10/16 10:53:14 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_texture_path(t_global_state *state, char *flag)
{
	t_game_params	*tmp;

	tmp = state->data->params;
	while (tmp)
	{
		if (!ft_strcmp (tmp->key, flag))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	load_textures(t_global_state *state)
{
	state->west_texture.img.img = mlx_xpm_file_to_image (state->vars->mlx,
			get_texture_path (state, "WE"),
			&state->west_texture.width, &state->west_texture.height);
	state->west_texture.img.addr = (int *)mlx_get_data_addr
		(state->west_texture.img.img,
			&(state->west_texture.img.bits_per_pixel),
			&(state->west_texture.img.line_length),
			&(state->west_texture.img.endian));
	state->east_texture.img.img = mlx_xpm_file_to_image (state->vars->mlx,
			get_texture_path (state, "EA"),
			&state->east_texture.width, &state->east_texture.height);
	state->east_texture.img.addr = (int *)mlx_get_data_addr
		(state->east_texture.img.img,
			&(state->east_texture.img.bits_per_pixel),
			&(state->east_texture.img.line_length),
			&(state->east_texture.img.endian));
}

void	init_player_attributes(t_global_state *state)
{
	state->flags->move_down = 0;
	state->flags->move_left = 0;
	state->flags->move_right = 0;
	state->flags->move_up = 0;
	state->flags->releaod = 0;
	state->flags->rotate_left = 0;
	state->flags->rotate_right = 0;
	state->flags->trigger = 0;
}

void	init_hooks(t_global_state *state, int flag)
{
	mlx_hook(state->vars->mlx_win, 2, (1L << 0), handle_keypress, state);
	mlx_hook (state->vars->mlx_win, 3, (1L << 1), handle_keyup, state);
	mlx_hook (state->vars->mlx_win, LEAVE_NOTIFY, 0, &handle_leave, state);
	if (flag)
		mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle, state);
	else
		mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle_2, state);
}

void	free_vars(char *path, char *indx, char *tmp)
{
	free (tmp);
	free (indx);
	free (path);
}
