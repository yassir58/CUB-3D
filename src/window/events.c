/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:01:37 by yelatman          #+#    #+#             */
/*   Updated: 2022/10/10 12:46:56 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_keypress(int keycode, t_global_state *state)
{
	if (keycode == XK_ESCAPE)
		handle_escape (state);
	else if (keycode == XK_UP)
		state->flags->move_up = 1;
	else if (keycode == XK_DOWN)
		state->flags->move_down = 1;
	else if (keycode == XK_LEFT)
		state->flags->move_left = 1;
	else if (keycode == XK_RIGHT)
		state->flags->move_right = 1;
	else if (keycode == R_LEFT)
		state->flags->rotate_left = 1;
	else if (keycode == R_RIGHT)
		state->flags->rotate_right = 1;
	else if (keycode == SHOOT)
	{
		play_sound (0);
		state->flags->trigger = 1;
	}
	else if (keycode == RELEAOD)
	{
		play_sound (1);
		state->flags->releaod = 1;
	}
	return (0);
}

int	handle_keyup(int keycode, t_global_state *state)
{
	if (keycode == XK_UP)
		state->flags->move_up = 0;
	else if (keycode == XK_DOWN)
		state->flags->move_down = 0;
	else if (keycode == XK_LEFT)
		state->flags->move_left = 0;
	else if (keycode == XK_RIGHT)
		state->flags->move_right = 0;
	else if (keycode == R_LEFT)
		state->flags->rotate_left = 0;
	else if (keycode == R_RIGHT)
		state->flags->rotate_right = 0;
	return (0);
}

int	handle_events(t_global_state *state)
{
	if (state->flags->move_up)
		move_player(UP, state);
	if (state->flags->move_down)
		move_player (DOWN, state);
	if (state->flags->move_left)
		move_player(LEFT, state);
	if (state->flags->move_right)
		move_player(RIGHT, state);
	if (state->flags->rotate_left)
		move_player (L, state);
	if (state->flags->rotate_right)
		move_player(R, state);
	return (0);
}

int	mouse_handle(int x, int y, void *param)
{
	t_global_state	*state;
	int				prev_pos;
	int				calc_pos;

	(void)y;
	state = (t_global_state *)param;
	prev_pos = state->data->prev_pos_mouse;
	if (x < 0)
		prev_pos *= -1;
	calc_pos = x - prev_pos;
	if (calc_pos < 0) 
		state->player->v_angle -= 2;
	else
		state->player->v_angle += 2;
	rerender_map(state);
	state->data->prev_pos_mouse = x;
	return (0);
}

int	mouse_handle_2(int x, int y, void *param)
{
	t_global_state	*state;
	int				prev_pos;
	int				calc_pos;

	(void)y;
	state = (t_global_state *)param;
	prev_pos = state->data->prev_pos_mouse;
	if (x < 0)
		prev_pos *= -1;
	calc_pos = x - prev_pos;
	if (calc_pos < 0)
		state->player->v_angle -= 2;
	else
		state->player->v_angle += 2;
	state->data->prev_pos_mouse = x;
	rerender_map_sprites (state);
	return (0);
}
