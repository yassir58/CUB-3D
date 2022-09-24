/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:54 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/23 18:29:20 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    correctPlayerAngle(t_global_state *state)
{
	if (state->player->v_angle < 0)
		state->player->v_angle += 360;
	else if (state->player->v_angle > 360)
		state->player->v_angle = state->player->v_angle % 360;
}

void move_player (int flag, t_global_state *state)
{
	double newPlayerX;
	double newPlayerY;
	int moveDirection;
	int rotationDirection;

	rotationDirection = 0;
	moveDirection = 0;
	if (flag == UP)
		moveDirection = 1;
	else if (flag == DOWN)
		moveDirection = -1;
	else if (flag == RIGHT)
	{
		newPlayerX = state->player->initx - state->player->move_speed * sin(deg_to_radian(state->player->v_angle));
		newPlayerY = state->player->inity + state->player->move_speed * cos(deg_to_radian(state->player->v_angle));
		if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
		{
			state->player->initx = newPlayerX;
			state->player->inity = newPlayerY;
		}
		return (rerender_map(state));
	}
	else if (flag == LEFT)
	{
		newPlayerX = state->player->initx + state->player->move_speed * sin(deg_to_radian(state->player->v_angle));
		newPlayerY = state->player->inity - state->player->move_speed * cos(deg_to_radian(state->player->v_angle));
		if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
		{
			state->player->initx = newPlayerX;
			state->player->inity = newPlayerY;
		}
		return (rerender_map(state));
	}
	else if (flag == L)
		rotationDirection = -1;
	else if (flag == R)
		rotationDirection = 1;
	state->player->v_angle += rotationDirection * ROTATION_SPEED;
	correctPlayerAngle(state);
	newPlayerX = state->player->initx + (moveDirection * state->player->move_speed) * cos(deg_to_radian(state->player->v_angle));
	newPlayerY = state->player->inity + (moveDirection * state->player->move_speed) * sin(deg_to_radian(state->player->v_angle));
	if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
	{
		state->player->initx = newPlayerX;
		state->player->inity = newPlayerY;
	}
	rerender_map (state);
}


void rerender_map (t_global_state *state)
{
	mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
	raycaster (state);
	draw_gun_pointer (0xFF0000, state);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
}


void rerender_map_sprites (t_global_state *state)
{
	mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
	raycaster (state);
	draw_gun_pointer (0xFF0000, state);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->current_sprite.img.img, (state->data->window_width) - state->current_sprite.width, state->data->window_height -  state->current_sprite.height);
}


void move_player_2 (int flag, t_global_state *state)
{
	double newPlayerX;
	double newPlayerY;
	int moveDirection;
	int rotationDirection;

	rotationDirection = 0;
	moveDirection = 0;
	if (flag == UP)
		moveDirection = 1;
	else if (flag == DOWN)
		moveDirection = -1;
	else if (flag == RIGHT)
	{
		newPlayerX = state->player->initx - state->player->move_speed * sin(deg_to_radian(state->player->v_angle));
		newPlayerY = state->player->inity + state->player->move_speed * cos(deg_to_radian(state->player->v_angle));
		if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
		{
			state->player->initx = newPlayerX;
			state->player->inity = newPlayerY;
		}
		return (rerender_map_sprites(state));
	}
	else if (flag == LEFT)
	{
		newPlayerX = state->player->initx + state->player->move_speed * sin(deg_to_radian(state->player->v_angle));
		newPlayerY = state->player->inity - state->player->move_speed * cos(deg_to_radian(state->player->v_angle));
		if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
		{
			state->player->initx = newPlayerX;
			state->player->inity = newPlayerY;
		}
		return (rerender_map_sprites(state));
	}
	else if (flag == L)
		rotationDirection = -1;
	else if (flag == R)
		rotationDirection = 1;
	state->player->v_angle += rotationDirection * ROTATION_SPEED;
	correctPlayerAngle(state);
	newPlayerX = state->player->initx + (moveDirection * state->player->move_speed) * cos(deg_to_radian(state->player->v_angle));
	newPlayerY = state->player->inity + (moveDirection * state->player->move_speed) * sin(deg_to_radian(state->player->v_angle));
	if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
	{
		state->player->initx = newPlayerX;
		state->player->inity = newPlayerY;
	}
	rerender_map_sprites (state);
}