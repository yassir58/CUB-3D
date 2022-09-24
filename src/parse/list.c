/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:44 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/24 20:17:30 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_game_params	*last_param(t_game_params *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	game_param_size(t_game_params *lst)
{
	int				i;
	t_game_params	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	add_param(t_game_params **lst, t_game_params *new)
{
	t_game_params	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = last_param(*lst);
	last_node->next = new;
}

t_map_line	*last_line(t_map_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_line(t_map_line **lst, t_map_line *new)
{
	t_map_line	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = last_line(*lst);
	last_node->next = new;
}
