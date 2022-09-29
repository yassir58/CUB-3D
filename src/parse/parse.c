/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:59 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/29 19:10:27 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_map_character(char c)
{
	if (ft_strchr(WALL_CHARS, c))
		return (1);
	return (0);
}

int	check_map_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == ' ')
		i += 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (check_map_character(str[i]))
			i += 1;
		else
			return (0);
	}
	return (1);
}

void	add_params_to_list(char *line, t_game_params **params_list)
{
	char	**splitted;
	char	*key;
	char	*value;

	splitted = NULL;
	if (check_spaces(line))
		splitted = get_key_value(line);
	if (splitted && ft_strlen(splitted[0]) && ft_strlen(splitted[1]))
	{
		key = strip_whitespaces(splitted[0]);
		value = strip_whitespaces(splitted[1]);
		if (!search_params_list(key, params_list))
		{
			if (check_identifier(key) == 2)
				value = ft_itoa(get_color(value));
			else if (check_identifier(key) == 1)
				check_path(value);
			else
				app_error(6);
			add_param(params_list, new_params(key, value));
		}
		else
			app_error(11);
	}
	free(splitted);
}

void	get_lists(int fd, t_game_data *data)
{
	int				i;
	char			*line;
	t_game_params	*params_list;
	t_map_line		*lines_list;

	i = 0;
	params_list = NULL;
	lines_list = NULL;
	line = advanced_get_next_line(fd, 0);
	while (line && !check_map_line(line))
	{
		add_params_to_list(line, &params_list);
		free(line);
		line = advanced_get_next_line(fd, 0);
	}
	while (line && check_map_line(line))
	{
		add_line(&lines_list, new_line(line));
		line = advanced_get_next_line(fd, 0);
	}
	if (line)
		app_error(1);
	data->params = params_list;
	data->lines = lines_list;
	close(fd);
}

// Still need to check why the map is not validating the closing of the map.

void	parse_map(char *path, t_global_state *state)
{
	int		fd;
	
	check_map_file(path);
	fd = open(path, O_RDONLY);
	get_lists(fd, state->data);
	if (game_param_size(state->data->params) != 6)
		app_error(11);
	if (!state->data->lines)
		app_error(2);
	state->data->map = validate_map(convert_lines_table(state->data->lines), \
	lines_number(state->data->lines), state);
}
