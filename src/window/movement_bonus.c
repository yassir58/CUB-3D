/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:49:11 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/25 12:57:26 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	correct_player_angle(t_global_state *state)
{
	if (state->player->v_angle < 0)
		state->player->v_angle += 360;
	else if (state->player->v_angle > 360)
		state->player->v_angle = state->player->v_angle % 360;
}

void	rerender_map_sprites(t_global_state *state)
{
	mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
	raycaster (state);
	draw_gun_pointer (0xFF0000, state);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, \
	state->img.img, 0, 0);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, \
	state->current_sprite.img.img, (state->data->window_width) - \
	state->current_sprite.width, state->data->window_height - \
	state->current_sprite.height);
}

void	move_player_2(int flag, t_global_state *state)
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
		move_right(flag, 1, state);
	else if (flag == LEFT)
		move_left(flag, 1, state);
	rotate_player(flag, 1, state);
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
	rerender_map_sprites(state);
}
