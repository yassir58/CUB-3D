/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:28 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/24 20:07:53 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_wall(double x, double y, t_global_state *state)
{
	double	check_x;
	double	check_y;

	check_x = floor(x / state->data->tile_x);
	check_y = floor(y / state->data->tile_y);
	if (!(check_x < state->grid->col && check_y < state->grid->row))
		return (1);
	if (state->data->map[(int)check_y][(int)check_x] == '1')
		return (1);
	return (0);
}

int	check_wall_move(double x, double y, t_global_state *state, int flag)
{
	double	check_x;
	double	check_y;
	int		move_speed;

	move_speed = state->player->move_speed;
	check_x = floor(x / state->data->tile_x);
	check_y = floor(y / state->data->tile_y);
	if (flag == UP && state->cast->distance_to_wall - move_speed < 2)
		return (1);
	else if (flag == DOWN && state->cast->distance_to_wall + move_speed < 2)
		return (1);
	if (!(check_x > 0 && check_x < state->grid->col && check_y > 0 \
	&& check_y < state->grid->row))
		return (1);
	if (state->data->map[(int)check_y][(int)check_x] == '1')
		return (1);
	return (0);
}
