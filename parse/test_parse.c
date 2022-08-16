#include "../includes/cub3d.h"


t_map_list *create_map_list (char *file)
{
    int fd;
    t_map_list *map;
    char *line;


    map = NULL ;
    fd = open (file, O_RDONLY);
    if (fd != -1)
    {
        while ((line  = get_next_line (fd)))
            push_to_list (&map, line);
    }
    return  (map);
}

void push_to_list (t_map_list **map, char *column)
{
    t_map_list *node;
    t_map_list *tmp;

    node = NULL;
    tmp = *map;
    if (!tmp)
    {
        tmp = malloc (sizeof (t_map_list));
        tmp->column = column;
        tmp->next = NULL;
        *map = tmp;
    }
    else
    {
        node = malloc (sizeof (t_map_list));
        node->column = column;
        node->next = NULL;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }
}