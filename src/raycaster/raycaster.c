/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:22 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/24 20:12:07 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_txt(t_global_state *state, t_raycast *data, double ray_angle)
{
	if (data->was_intersection_vertical)
	{
		if (ray_facing_left(ray_angle))
			state->current = state->west_texture;
		else
			state->current = state->east_texture;
		data->coff = data->wall_hit_y / state->data->tile_x - \
		(int)(data->wall_hit_y / state->data->tile_x);
		data->off_x = (int)(data->coff * state->current.width);
	}
	else
	{
		if (ray_facing_up(ray_angle))
			state->current = state->north_texture;
		else
			state->current = state->south_texture;
		data->coff = data->wall_hit_x / state->data->tile_x - \
		(int)(data->wall_hit_x / state->data->tile_x);
		data->off_x = (int)(data->coff * state->current.height);
	}
}

double	cast_ray(double ray_angle, t_raycast *data, t_global_state *state)
{
	horz_ray(ray_angle, data, state);
	vert_ray(ray_angle, data, state);
	calculate_ray_distance(state, data);
	if (data->vertical_distance > data->horizontal_distance)
	{
		data->was_intersection_vertical = false;
		data->ray_distance = data->horizontal_distance;
		data->wall_hit_x = data->wall_horz_hit_x;
		data->wall_hit_y = data->wall_horz_hit_y;
	}
	else
	{
		data->was_intersection_vertical = true;
		data->ray_distance = data->vertical_distance;
		data->wall_hit_x = data->wall_vert_hit_x;
		data->wall_hit_y = data->wall_vert_hit_y;
	}
	render_txt(state, data, ray_angle);
	return (data->ray_distance * \
	cos(deg_to_rad(state->player->v_angle) - ray_angle));
}

void	horz_ray(double ray_angle, t_raycast *data, t_global_state *state)
{
	hintercept(ray_angle, data, state);
	data->next_h_touch_x = data->xintercept;
	data->next_h_touch_y = data->yintercept;
	if (ray_facing_up(ray_angle))
		data->next_h_touch_y -= 1;
	while (data->next_h_touch_x >= 0 && data->next_h_touch_x <= RES_X \
	&& data->next_h_touch_y >= 0 && data->next_h_touch_y <= RES_Y)
	{
		if (check_wall(data->next_h_touch_x, data->next_h_touch_y, state))
		{
			data->wall_horz_intesected = true;
			if (ray_facing_up(ray_angle))
				data->next_h_touch_y += 1;
			data->wall_horz_hit_x = data->next_h_touch_x;
			data->wall_horz_hit_y = data->next_h_touch_y;
			break ;
		}
		else
		{
			data->next_h_touch_x += data->xstep;
			data->next_h_touch_y += data->ystep;
		}
	}
}

void	vert_ray(double ray_angle, t_raycast *data, t_global_state *state)
{
	vintercept(ray_angle, data, state);
	data->next_vert_touchx = data->xintercept;
	data->next_vert_touchy = data->yintercept;
	if (ray_facing_left(ray_angle))
		data->next_vert_touchx -= 1;
	while (data->next_vert_touchx >= 0 && data->next_vert_touchx <= RES_X \
	&& data->next_vert_touchy >= 0 && data->next_vert_touchy <= RES_Y)
	{
		if (check_wall(data->next_vert_touchx, data->next_vert_touchy, state))
		{
			data->wall_vert_intesected = true;
			if (ray_facing_left(ray_angle))
				data->next_vert_touchx += 1;
			data->wall_vert_hit_x = data->next_vert_touchx;
			data->wall_vert_hit_y = data->next_vert_touchy;
			break ;
		}
		else
		{
			data->next_vert_touchx += data->xstep;
			data->next_vert_touchy += data->ystep;
		}
	}
}

void	raycaster(t_global_state *state)
{
	int		column_id;
	double	ray_angle;
	double	ray_distance;
	double	col_height;

	column_id = 0;
	col_height = 0;
	ray_distance = 0;
	ray_angle = deg_to_rad(state->player->v_angle) - (state->player->fov / 2.0);
	state->cast->pp_distance = (RES_X_2) / (tan(state->player->fov / 2.0));
	color(state, state->data->floor, RES_Y_2);
	color(state, state->data->ceil, 0);
	while (column_id < RES_X)
	{
		ray_distance = cast_ray(correct_angle(ray_angle), state->cast, state);
		if (column_id == RES_X_2)
			state->cast->distance_to_wall = ray_distance;
		col_height = (state->data->tile_y / ray_distance) * \
		state->cast->pp_distance;
		draw_column (column_id, ((RES_Y_2) - (col_height / 2)), \
		state, col_height);
		ray_angle += state->player->fov / RES_X;
		column_id += 1;
	}
	draw_minimap (state);
}
