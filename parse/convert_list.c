#include "../includes/cub3d.h"

char **convert_lines_table(t_map_line *list)
{
    int i;
    int num_lines;
    char **lines_table;
    t_map_line *tmp;

    i = 0;
    tmp = list;
    num_lines = lines_number(list);
    lines_table = (char **)malloc(sizeof(char *) * (num_lines + 1));
    if (!lines_table)
        return (NULL);
    while (tmp != NULL)
    {
        //! Possible leak
        lines_table[i++] = ft_strdup(tmp->line);
        tmp = tmp->next;
    }
    lines_table[i] = NULL;
    return (lines_table);
}

int string_table_number(char **table)
{
    int i;

    i = 0;
    while (table[i])
        i++;
    return (i);
}