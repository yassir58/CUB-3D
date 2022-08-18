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

void	add_param(t_game_params **lst, t_game_params *new)
{
	new->next = *lst;
	*lst = new;
}

int search_params_list(char *key, t_game_params *list)
{
    t_game_params *tmp;

    tmp = list;
    while (tmp != NULL)
    {
        if (ft_strcmp(key, tmp->key))
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
        printf("Key:%s = Value:%s\n", tmp->key ,tmp->value);
        tmp = tmp->next;
    }
}