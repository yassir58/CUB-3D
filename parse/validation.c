/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:18:24 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 15:19:07 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_map_line(char *line, char *prevline, char *nextline)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
		{
			if (!((line[i - 1] && line[i - 1] != ' ') && (line[i + 1] && \
			line[i + 1 != ' ']) && (prevline[i] && prevline[i] != ' ') && \
			(nextline[i] && nextline[i] != ' ')))
				app_error(8);
		}
		i += 1;
	}
	return (0);
}

int	validate_map_hor_walls(char **map, int size)
{
	if (!wall_line(map[0]) || !wall_line(map[size - 1]))
		return (0);
	return (1);
}

void	validate_player_occurrence(char **map, t_game_data *data)
{
	bool	player;
	int		i;
	int		j;

	i = 0;
	j = 0;
	player = false;
	while (map[i])
	{
		while (map[i][j] != '\0')
		{
			if (ft_strchr(PLAYER_CHARS, map[i][j]) && !player)
			{
				data->playerDirection = map[i][j];
				player = true;
			}
			else if (ft_strchr(PLAYER_CHARS, map[i][j]) && player)
				app_error(9);
			j++;
		}
		j = 0;
		i++;
	}
	if (!player)
		app_error(10);
}

void	validate_player_position(char *line)
{
	if (ft_strchr(PLAYER_CHARS, line[0]) || \
	ft_strchr(PLAYER_CHARS, line[ft_strlen(line) - 1]))
		app_error(7);
}

char	**validate_map(char **map, int map_size, t_global_state *state)
{
	int	i;

	i = 1;
	if (validate_map_hor_walls(map, map_size))
	{
		validate_player_occurrence(map, state->data);
		while (i < map_size - 1)
		{
			validate_player_position(map[i]);
			validate_map_line(map[i], map[i - 1], map[i + 1]);
			i += 1;
		}
	}
	else
		app_error(8);
	return (map);
}
