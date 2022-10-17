/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:01:33 by yelatman          #+#    #+#             */
/*   Updated: 2022/10/17 11:17:43 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_global_state *state, int x, int y, int color)
{
	t_img	*data;

	data = &state->img;
	if ((x >= 0 && x < state->data->window_width)
		&& (y >= 0 && y < state->data->window_height))
		data->addr[(state->data->window_width * y) + x] = color;
}

void	draw_minirect(int x, int y, int color, t_global_state *state)
{
	int	i;
	int	j;
	int	clr;

	i = 0;
	j = 0;
	clr = 0;
	while (i <= MINIMAP_CEL)
	{
		while (j <= MINIMAP_CEL)
		{
			clr = color;
			my_mlx_pixel_put (state, (x + j), (y + i), clr);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_column(int x, int y, t_global_state *state, double colHeight)
{
	int	start;
	int	end;
	int	texel_clr;
	int	off_y;

	start = y;
	if(start < 0)
		start = 0;
	end = colHeight;
	if(end > RES_Y)
		end = RES_Y;
	while (end--)
	{
		off_y = (start - y) * (state->current.height / colHeight);
		texel_clr = state->current.img.addr[(
				state->current.width * off_y) + state->cast->off_x];
		my_mlx_pixel_put (state, x, start, texel_clr);
		start++;
	}
}

int	handle_events_2(t_global_state *state)
{
	if (state->flags->move_up)
		move_player_2 (UP, state);
	if (state->flags->move_down)
		move_player_2 (DOWN, state);
	if (state->flags->move_left)
		move_player_2 (LEFT, state);
	if (state->flags->move_right)
		move_player_2 (RIGHT, state);
	if (state->flags->rotate_left)
		move_player_2 (L, state);
	if (state->flags->rotate_right)
		move_player_2 (R, state);
	handle_shoot_sprite (state);
	return (0);
}

void	set_colors(t_global_state *state)
{
	t_game_params	*tmp;

	tmp = state->data->params;
	while (tmp)
	{
		if (!ft_strcmp (tmp->key, "C"))
			state->data->ceil = ft_atoi (tmp->value);
		if (!ft_strcmp (tmp->key, "F"))
			state->data->floor = ft_atoi (tmp->value);
		tmp = tmp->next;
	}
}
