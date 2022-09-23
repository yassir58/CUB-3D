/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:59 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 15:19:19 by ochoumou         ###   ########.fr       */
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
	int		color;

	splitted = get_key_value(line);
	if (ft_strlen(splitted[0]) && ft_strlen(splitted[1]))
	{
		key = strip_whitespaces(splitted[0]);
		value = strip_whitespaces(splitted[1]);
		if (!search_params_list(key, params_list))
		{
			if (check_identifier(key) == 2)
			{
				color = get_color(value);
				free(value);
				value = ft_itoa(color);
			}
			else if (check_identifier(key) == 1)
				check_path(value);
			else
				app_error(6);
			add_param(params_list, new_params(key, value));
		}
		else
			app_error(3);
	}
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
	while (!check_map_line(line))
	{
		add_params_to_list(line, &params_list);
		free(line);
		line = advanced_get_next_line(fd, 0);
	}
	while (check_map_line(line))
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

void	parse_map(char *path, t_global_state *state)
{
	int	fd;

	validate_extension(path, ".cub");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		app_error(5);
	get_lists(fd, state->data);
	if (game_param_size(state->data->params) != 6)
		app_error(11);
	state->data->map = validate_map(convert_lines_table(state->data->lines), \
	lines_number(state->data->lines), state);
}