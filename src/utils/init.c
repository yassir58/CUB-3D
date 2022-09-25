/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:01:45 by yelatman          #+#    #+#             */
/*   Updated: 2022/09/25 15:02:29 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_global_state	*init_simulation_data(char **argv)
{
	t_global_state	*state;

	state = (t_global_state *)malloc(sizeof(t_global_state));
	if (!state)
		return (NULL);
	state->data = (t_game_data *)malloc(sizeof(t_game_data));
	state->grid = (t_grid_data *)malloc(sizeof(t_grid_data));
	state->player = (t_player *)malloc(sizeof(t_player));
	state->vars = (t_vars *)malloc(sizeof(t_vars));
	state->cast = (t_raycast *)malloc(sizeof(t_raycast));
	state->flags = (t_flags *)malloc (sizeof(t_flags));
	if (!state->data || !state->grid || !state->player
		|| !state->vars || !state->cast)
		return (NULL);
	parse_map(argv[1], state);
	calculate_grid (state->data->map, &(state->grid->col), &(state->grid->row));
	state->data->window_height = (RES_Y);
	state->data->window_width = (RES_X);
	state->data->tile_x = state->data->window_width / state->grid->col;
	state->data->tile_y = state->data->window_height / state->grid->row;
	state->data->prev_pos_mouse = state->data->window_width / 2;
	state->flags->speed_factor = state->data->window_width
		/ (state->grid->col * state->grid->row);
	init_player (state);
	return (state);
}

void	init_window(t_global_state *state)
{
	state->vars->mlx = mlx_init ();
	state->vars->mlx_win = mlx_new_window (state->vars->mlx,
			state->data->window_width,
			state->data->window_height, "Insurgency: Sandstorm");
	state->img.img = mlx_new_image (state->vars->mlx, state->data->window_width,
			state->data->window_height);
	state->img.addr = (int *)mlx_get_data_addr (state->img.img,
			&(state->img.bits_per_pixel),
			&(state->img.line_length), &(state->img.endian));
}

char	**get_map_vector(t_map_list *list, t_global_state *state)
{
	char		**map_vector;
	t_map_list	*tmp;
	int			i;

	i = 0;
	tmp = list;
	map_vector = malloc (sizeof (char *) * (state->grid->row + 1));
	if (!map_vector)
		return (NULL);
	while (tmp)
	{
		map_vector[i] = ft_strdup (tmp->column);
		tmp = tmp->next;
		i++;
	}
	map_vector[i] = NULL;
	return (map_vector);
}

int	get_angle(char direction)
{
	if (direction == 'N')
		return (270);
	else if (direction == 'S')
		return (90);
	else if (direction == 'E')
		return (360);
	else if (direction == 'W')
		return (180);
	else
		return (90);
}

void	init_player(t_global_state *state)
{
	state->player->initx = 0;
	state->player->inity = 0;
	state->player->radius = 2;
	state->player->turn_direction = 0;
	state->player->walk_direction = 0;
	state->player->x_cord = 0;
	state->player->y_cord = 0;
	state->player->d_x = 0;
	state->player->d_y = 0;
	state->player->d_length = 50;
	state->player->v_angle = get_angle(state->data->player_direction);
	state->player->fov = (FOV * (M_PI / 180));
	state->player->rot_angle = (M_PI / 2);
	if (state->flags->speed_factor == 0)
		state->player->move_speed = 1;
	else
		state->player->move_speed = 4;
	if (state->data->tile_x < state->data->tile_y)
		state->data->tile_y = state->data->tile_x;
	else
		state->data->tile_x = state->data->tile_y;
	init_player_attributes (state);
}
