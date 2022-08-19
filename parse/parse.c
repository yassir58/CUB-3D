#include "../includes/cub3d.h"

void    app_error()
{
    printf("Warning: Parse error exiting\n");
    exit(1);
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

// Formulat to convert rgb to int: rgb = 65536 * r + 256 * g + b;

int get_color(char *str)
{
    char **rgb;
    int color;
    
    rgb = ft_split(str, ',');
    color = 0;
    if (count_seperator(str, ',') == 2)
    {
        if (ft_atoi(rgb[0]) <= 255 && ft_atoi(rgb[1]) <= 255 && ft_atoi(rgb[2]) <= 255)
        {
            color = 65536 * ft_atoi(rgb[0]) + 256 * ft_atoi(rgb[1]) + ft_atoi(rgb[2]);
            return (color);
        }
        else
            app_error();
    }
    return (-1);
}

int check_map_character(char c)
{
    if(ft_strchr(WALL_CHARS, c))
        return (1);
    return (0);
}

int check_map_line(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i] && str[i] == ' ')
        i += 1;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (check_map_character(str[i]))
            i += 1;
        else
            return (0);
    }
    return (1);
}

void    add_params_to_list(char *line, t_game_params **params_list)
{
    char **splitted;
    char *key;
    char *value;

    splitted = ft_split(line, ' ');
    if (splitted[0] && splitted[1])
    {
        key = ft_strdup(splitted[0]);
        value = ft_strdup(splitted[1]);
        if (!search_params_list(key, params_list))
        {
            if (!ft_strcmp(key, "F") || !ft_strcmp(key, "C"))
            {
                // !LEAK
                value = ft_itoa(get_color(value));
            }
            add_param(params_list, new_params(key, value));
        }
        else
            app_error();
    }
}

void    get_lists(int fd, t_game_data *data)
{
    char *line;
    t_game_params *params_list;
    t_map_line *lines_list;

    params_list = NULL;
    // Still not sure weather we need all the information to validate the map 
    line = advanced_get_next_line(fd, 0);
    while (!check_map_line(line))
    {
        add_params_to_list(line, &params_list);
        line = advanced_get_next_line(fd, 0);
    }
    while (check_map_line(line))
    {
        add_line(&lines_list, new_line(line));
        line = advanced_get_next_line(fd, 0);
    }
    data->params = params_list;
    data->lines = lines_list;
}

void    parse_map(char *path, t_game_data *data)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return ;
    get_lists(fd, data);
    print_params_list(data->params);
    print_lines_list(data->lines);
    // open the map and send fd to the appropriate function so it can get the game params.
}