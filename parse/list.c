#include "../includes/cub3d.h"

t_game_params	*new_params(char *key, char *value, int index)
{
	t_game_params	*new_list;

	new_list = (t_game_params *)malloc(sizeof(t_game_params));
	if (!new_list)
		return (NULL);
    new_list->key = key;
	new_list->value = value;
    new_list->index = index;
	new_list->next = NULL;
	return (new_list);
}

int lines_number(t_map_line *list)
{
    int i;
    t_map_line *tmp;

    i = 0;
    tmp = list;
    while (tmp != NULL)
    {
        i += 1;
        tmp = tmp->next;
    }
    return (i);
}

t_game_params   *last_param(t_game_params *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
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

t_map_line	*new_line(char *line)
{
	t_map_line  *new_list;

	new_list = (t_map_line *)malloc(sizeof(t_map_line));
	if (!new_list)
		return (NULL);
    new_list->line = line;
	new_list->next = NULL;
	return (new_list);
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

int search_params_list(char *key, t_game_params **list)
{
    t_game_params *tmp;

    tmp = *list;
    while (tmp != NULL)
    {
        if (!ft_strcmp(key, tmp->key))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void    print_params_list(t_game_params *list)
{
    t_game_params *tmp;

    tmp = list;
    while (tmp != NULL)
    {
        printf("Key:%s Value:%s Index:%d\n", tmp->key ,tmp->value, tmp->index);
        tmp = tmp->next;
    }
}

void    print_lines_list(t_map_line *list)
{
    t_map_line *tmp;

    tmp = list;
    while (tmp != NULL)
    {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
}