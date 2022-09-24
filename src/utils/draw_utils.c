/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:01:49 by yelatman          #+#    #+#             */
/*   Updated: 2022/09/24 15:05:53 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap(t_global_state *state)
{
	int	j ;
	int	y ;
	int	indx_x;
	int	indx_y;

	j = 0;
	y = 0;
	state->player->minimap_x = position_in_map (state->player->initx, state);
	state->player->minimap_y = position_in_map (state->player->inity, state);
	indx_x = state->player->minimap_x - ((MINIMAP_ROW / 2));
	indx_y = state->player->minimap_y - (MINIMAP_ROW / 2);
	while (j < MINIMAP_ROW)
	{
		if ((indx_y + j >= 0 && indx_y + j < state->grid->row))
			draw_minimap_row (y, state, indx_x, indx_y + j);
		else
			draw_minimap_wall (y, state, indx_x);
		y += MINIMAP_CEL;
		j++;
	}
}

void	render_minimap_cel(int x, int y, t_global_state *state, int elm)
{
	if (elm == 'p')
		draw_minirect (x, y, 0x00FF0156, state);
	else if (elm == '0' || elm == ' ' || elm == 'N'
		|| elm == 'S' || elm == 'W' || elm == 'E')
		draw_minirect (x, y, 0x00000000, state);
	else
		draw_minirect (x, y, 0x00FFF80A, state);
}

void	draw_minimap_row(int y, t_global_state *state, int indx_x, int indx_y)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < MINIMAP_ROW)
	{
		if (indx_x + i == state->player->minimap_x
			&& indx_y == state->player->minimap_y)
			render_minimap_cel (x, y, state, 'p');
		else if ((indx_x + i >= 0 && indx_x + i <= state->grid->col))
			render_minimap_cel (x, y, state,
				state->data->map[indx_y][indx_x + i]);
		else
			render_minimap_cel (x, y, state, ' ');
			x += MINIMAP_CEL;
		i++;
	}
}

void	draw_minimap_wall(int y, t_global_state *state, int indx_x)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (i < MINIMAP_ROW)
	{
		if ((indx_x + i >= 0 && indx_x + i < state->grid->col))
			render_minimap_cel (x, y, state, '0');
		else
			draw_minirect (x, y, 0x00000000, state);
		x += MINIMAP_CEL;
		i++;
	}
}

void	minimap_position(t_global_state *state)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (i < state->grid->row)
	{
		while (j < state->grid->col)
		{
			if (state->data->map[i][j] == state->data->player_direction)
				set_player_position (state, x, y);
			x += MINIMAP_CEL;
			j++;
		}
		j = 0;
		x = 0;
		y += MINIMAP_CEL;
		i++;
	}
}
