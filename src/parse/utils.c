/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:18:06 by ochoumou          #+#    #+#             */
/*   Updated: 2022/10/09 11:03:04 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_identifier(char *id)
{
	if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "WE") || \
	!ft_strcmp(id, "EA"))
		return (1);
	else if (!ft_strcmp(id, "F") || !ft_strcmp(id, "C"))
		return (2);
	return (0);
}

void	check_path(char *path)
{
	int		fd;
	char	buff[1];

	buff[0] = 0;
	fd = open(path, O_RDONLY);
	validate_extension(path, ".xpm");
	read(fd, buff, 1);
	if (!buff[0])
		app_error(12);
	close(fd);
	if (fd < 0)
		app_error(5);
}

void	validate_extension(char *path, char *ext)
{
	int	size;

	size = ft_strlen(path) - 4;
	if (ft_strcmp(ext, path + size))
		app_error(4);
}

void	validate_color_number(char **table)
{
	int	i;
	int	j;

	i = 0;
	while (table[i])
	{
		j = 0;
		while (table[i][j])
		{
			if (ft_isdigit(table[i][j]) || table[i][j] == ' ')
				j++;
			else
				app_error(3);
		}
		if (!check_spaces(table[i]))
			app_error(3);
		i += 1;
	}
}

// Formulat to convert rgb to int: rgb = 65536 * r + 256 * g + b;
int	get_color(char *str)
{
	char	**rgb;
	int		color;

	color = 0;
	rgb = ft_split(str, ',');
	validate_color_number(rgb);
	if (count_seperator(str, ',') == 2)
	{
		if (ft_atoi(rgb[0]) <= 255 && ft_atoi(rgb[1]) <= 255 \
		&& ft_atoi(rgb[2]) <= 255)
		{
			color = 65536 * ft_atoi(rgb[0]) + 256 * ft_atoi(rgb[1]) \
			+ ft_atoi(rgb[2]);
			free_table(rgb);
			free(str);
			return (color);
		}
		else
			app_error(3);
	}
	else
		app_error(3);
	return (-1);
}
