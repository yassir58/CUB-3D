/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:55 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/27 12:11:06 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	wall_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(WALL_LINE, line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**get_key_value(char *str)
{
	char	**keys;
	int		i;
	int		j;
	int		saved;

	i = 0;
	j = 0;
	keys = (char **)malloc(sizeof(char *) * 3);
	if (!keys)
		return (NULL);
	while (str[i] && str[i] == ' ')
		i++;
	saved = i;
	while (str[i] && str[i] != ' ')
	{
		i++;
		j++;
	}
	keys[0] = ft_substr(str, saved, j);
	i += j;
	while (str[i] && str[i] == ' ')
		i++;
	keys[1] = ft_strdup(str + i - 1);
	keys[2] = NULL;
	return (keys);
}

char	*strip_whitespaces(char *str)
{
	int		start;
	int		end;
	char	*clean;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && str[start] == ' ')
		start++;
	while (str[end] && str[end] == ' ')
		end--;
	clean = ft_substr(str, start, end - start + 1);
	free(str);
	return (clean);
}
