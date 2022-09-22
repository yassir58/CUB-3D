/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:41 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 13:22:14 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_game_params	*new_params(char *key, char *value)
{
	t_game_params	*new_list;

	new_list = (t_game_params *)malloc(sizeof(t_game_params));
	if (!new_list)
		return (NULL);
	new_list->key = key;
	new_list->value = value;
	new_list->next = NULL;
	return (new_list);
}

t_map_line	*new_line(char *line)
{
	t_map_line	*new_list;

	new_list = (t_map_line *)malloc(sizeof(t_map_line));
	if (!new_list)
		return (NULL);
	new_list->line = line;
	new_list->next = NULL;
	return (new_list);
}

int	search_params_list(char *key, t_game_params **list)
{
	t_game_params	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if (!ft_strcmp(key, tmp->key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	lines_number(t_map_line *list)
{
	int			i;
	t_map_line	*tmp;

	i = 0;
	tmp = list;
	while (tmp != NULL)
	{
		i += 1;
		tmp = tmp->next;
	}
	return (i);
}
