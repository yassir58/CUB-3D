/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:01:28 by yelatman          #+#    #+#             */
/*   Updated: 2022/09/23 16:26:12 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_for_wall(int x, int y, t_global_state *state)
{
	int	indx_x;
	int	indx_y;

	indx_x = position_in_map (x, state);
	indx_y = position_in_map (y, state);
	if (state->data->map[indx_y][indx_x] != '1')
		return (1);
	return (0);
}

int	position_in_map(int cord, t_global_state *state)
{
	int	n;

	n = cord / state->data->tile_x;
	return (n);
}

void	get_player_position(int *row, int *col, t_global_state *state)
{
	int	i;
	int	j;

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
				break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_gun_pointer(int color, t_global_state *state)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;
	double	j;

	i = 0.0;
	j = 0.0;
	state->player->d_x = state->data->window_width / 2;
	state->player->d_y = state->data->window_height / 2;
	while (j <= state->player->radius)
	{
		while (i < 360)
		{
			angle = i;
			x1 = j * cos(angle * (M_PI / 180));
			y1 = j * sin (angle * (M_PI / 180));
			my_mlx_pixel_put (state, (state->player->d_x + x1),
				(state->player->d_y + y1), color);
			i += 0.1;
		}
		i = 0;
		j += 0.1;
	}
}

void	handle_escape(t_global_state *state)
{
	mlx_destroy_window(state->vars->mlx, state->vars->mlx_win);
	exit (EXIT_SUCCESS);
}
