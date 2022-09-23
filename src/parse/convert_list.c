/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:24 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 13:20:46 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**convert_lines_table(t_map_line *list)
{
	int			i;
	int			num_lines;
	char		**lines_table;
	t_map_line	*tmp;

	i = 0;
	tmp = list;
	num_lines = lines_number(list);
	lines_table = (char **)malloc(sizeof(char *) * (num_lines + 1));
	if (!lines_table)
		return (NULL);
	while (tmp != NULL)
	{
		lines_table[i++] = ft_strdup(tmp->line);
		tmp = tmp->next;
	}
	lines_table[i] = NULL;
	return (lines_table);
}

int	number_of_el(char **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
		i++;
	return (i);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (i < number_of_el(map))
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	count_seperator(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count += 1;
		i++;
	}
	return (count);
}
