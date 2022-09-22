#include "../includes/cub3d.h"

t_game_params   *last_param(t_game_params *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	game_param_size(t_game_params *lst)
{
	int i;
	t_game_params *tmp;

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

// void    print_params_list(t_game_params *list)
// {
//     t_game_params *tmp;

//     tmp = list;
//     while (tmp != NULL)
//     {
//         printf("Key:|%s| Value:|%s|\n", tmp->key ,tmp->value);
//         tmp = tmp->next;
//     }
// }

// void    print_lines_list(t_map_line *list)
// {
//     t_map_line *tmp;

//     tmp = list;
//     while (tmp != NULL)
//     {
//         printf("%s\n", tmp->line);
//         tmp = tmp->next;
//     }
// }