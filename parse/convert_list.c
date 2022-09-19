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
        lines_table[i++] = ft_strdup(tmp->line);
        tmp = tmp->next;
    }
    lines_table[i] = NULL;
    return (lines_table);
}

int number_of_el(char **table)
{
    int i;

    i = 0;
    while (table[i] != NULL)
        i++;
    return (i);
}

int count_seperator(char *str, char c)
{
    int count;
    int i;

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