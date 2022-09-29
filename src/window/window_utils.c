/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:01:13 by yelatman          #+#    #+#             */
/*   Updated: 2022/09/29 16:02:43 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_leave(t_global_state *state)
{
	(void)state;
	exit (EXIT_SUCCESS);
	return (0);
}

int	handle_shoot_sprite(t_global_state *state)
{
	static int	i;
	static int	j;

	if (state->flags->trigger)
	{
		state->current_sprite = state->sprites[i++];
		if (i == 5)
		{
			state->flags->trigger = 0;
			i = 0;
		}
	}
	else if (state->flags->releaod)
	{
		state->current_sprite = state->releaod_sprites[j++];
		if (j == 10)
		{
			state->flags->releaod = 0;
			j = 0;
			state->current_sprite = state->sprites[0];
		}
	}
	rerender_map_sprites (state);
	return (0);
}

void	play_sound(int flag)
{
	int	id;

	id = fork ();
	if (id == 0)
	{
		if (flag == 0)
			system ("afplay assets/firing.mp3");
		if (flag == 1)
			system ("afplay assets/reloading.mp3");
		exit (EXIT_SUCCESS);
	}
}

void	set_player_position(t_global_state *state, int x, int y)
{
	state->player->initx = x + (state->data->tile_x / 2);
	state->player->inity = y + (state->data->tile_x / 2);
	state->player->minimap_x = x + (MINIMAP_CEL / 2);
	state->player->minimap_y = y + (MINIMAP_CEL / 2);
}
