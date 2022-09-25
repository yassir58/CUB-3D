/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:54 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/25 12:57:53 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_left(int flag, int render, t_global_state *state)
{
	double	new_player_x;
	double	new_player_y;

	new_player_x = state->player->initx + state->player->move_speed \
	* sin(deg_to_rad(state->player->v_angle));
	new_player_y = state->player->inity - state->player->move_speed \
	* cos(deg_to_rad(state->player->v_angle));
	if (!check_wall_move(new_player_x, new_player_y, state, flag))
	{
		state->player->initx = new_player_x;
		state->player->inity = new_player_y;
	}
	if (render)
		return (rerender_map_sprites(state));
	return (rerender_map(state));
}

void	move_right(int flag, int render, t_global_state *state)
{
	double	new_player_x;
	double	new_player_y;

	new_player_x = state->player->initx - state->player->move_speed \
	* sin(deg_to_rad(state->player->v_angle));
	new_player_y = state->player->inity + state->player->move_speed \
	* cos(deg_to_rad(state->player->v_angle));
	if (!check_wall_move(new_player_x, new_player_y, state, flag))
	{
		state->player->initx = new_player_x;
		state->player->inity = new_player_y;
	}
	if (render)
		return (rerender_map_sprites(state));
	return (rerender_map(state));
}

void	rotate_player(int flag, int render, t_global_state *state)
{
	int	rotation_direction;

	rotation_direction = 0;
	if (flag == L)
		rotation_direction = -1;
	else if (flag == R)
		rotation_direction = 1;
	state->player->v_angle += rotation_direction * ROTATION_SPEED;
	correct_player_angle(state);
	if (render)
		return (rerender_map_sprites(state));
	return (rerender_map(state));
}

void	move_player(int flag, t_global_state *state)
{
	int		move_direction;
	double	new_player_x;
	double	new_player_y;

	move_direction = 0;
	if (flag == UP)
		move_direction = 1;
	else if (flag == DOWN)
		move_direction = -1;
	else if (flag == RIGHT)
		move_right(flag, 0, state);
	else if (flag == LEFT)
		move_left(flag, 0, state);
	rotate_player(flag, 0, state);
	new_player_x = state->player->initx + (move_direction * \
	state->player->move_speed) \
	* cos(deg_to_rad(state->player->v_angle));
	new_player_y = state->player->inity + (move_direction * \
	state->player->move_speed) * sin(deg_to_rad(state->player->v_angle));
	if (!check_wall_move(new_player_x, new_player_y, state, flag))
	{
		state->player->initx = new_player_x;
		state->player->inity = new_player_y;
	}
	rerender_map (state);
}

void	rerender_map(t_global_state *state)
{
	mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
	raycaster (state);
	draw_gun_pointer (0xFF0000, state);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, \
	state->img.img, 0, 0);
}
