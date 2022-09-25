/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:09:03 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/25 13:51:10 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	calculate_distance(double xp, double xa, double angle)
{
	double	distance;

	distance = fabs((xp - xa) / cos(angle));
	return (distance);
}

void	calculate_ray_distance(t_global_state *s, t_raycast *data, double ang)
{
	if (data->wall_horz_intesected)
		data->horizontal_distance = calculate_distance(s->player->initx, \
		data->wall_horz_hit_x, ang);
	else
		data->horizontal_distance = INT_MAX;
	if (data->wall_vert_intesected)
		data->vertical_distance = calculate_distance(s->player->initx, \
		data->wall_vert_hit_x, ang);
	else
		data->vertical_distance = INT_MAX;
}

void	vintercept(double ray_angle, t_raycast *data, t_global_state *state)
{
	int	tile_x;

	tile_x = state->data->tile_x;
	data->wall_vert_intesected = false;
	data->xintercept = floor(state->player->initx / tile_x) * tile_x;
	if (ray_facing_right(ray_angle))
		data->xintercept += tile_x;
	data->yintercept = state->player->inity + ((data->xintercept - \
	state->player->initx) * tan(ray_angle));
	data->xstep = tile_x;
	if (ray_facing_left(ray_angle))
		data->xstep *= -1;
	data->ystep = data->xstep * tan(ray_angle);
	if (ray_facing_up(ray_angle) && data->ystep > 0)
		data->ystep *= -1;
	if (ray_facing_down(ray_angle) && data->ystep < 0)
		data->ystep *= -1;
}

void	hintercept(double ray_angle, t_raycast *data, t_global_state *state)
{
	int	tile_y;

	tile_y = state->data->tile_y;
	data->wall_horz_intesected = false;
	data->yintercept = floor(state->player->inity / tile_y) * tile_y;
	if (ray_facing_down(ray_angle))
		data->yintercept += tile_y;
	data->xintercept = state->player->initx + ((data->yintercept - \
	state->player->inity) / tan(ray_angle));
	data->ystep = tile_y;
	if (!ray_facing_down(ray_angle))
		data->ystep *= -1;
	data->xstep = data->ystep / tan(ray_angle);
	if (ray_facing_left(ray_angle) && data->xstep > 0)
		data->xstep *= -1;
	if (ray_facing_right(ray_angle) && data->xstep < 0)
		data->xstep *= -1;
}
