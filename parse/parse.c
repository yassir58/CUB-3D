#include "../includes/cub3d.h"

void    app_error(int code)
{
    //! In this function we should free all the allocated lists before exit.
    if (code == 1)
        printf("Error: parse error exiting\n");
    else if (code == 2)
        printf("Error: invalid map exiting\n");
    else if (code == 3)
        printf("Error: map colors are incorrect\n");
    else if (code == 4)
        printf("Error: invalid map extension\n");
    else if (code == 5)
        printf("Error: could not open file.\n");
    exit(1);
}

// !TODO: 
//     + Validate the map extension.
//     + Check that every texture file exits if its not return an error.

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
            app_error(3);
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

void    check_path(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    close(fd);
    if (fd < 0)
        app_error(5);
}

void    add_params_to_list(char *line, t_game_params **params_list)
{
    char **splitted;
    char *key;
    char *value;
    int color;

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
                color = get_color(value);
                if (color == -1)
                    app_error(3);
                value = ft_itoa(color);
            }
            add_param(params_list, new_params(key, value));
        }
        else
            app_error(3);
    }
}

int number_of_el(char **table)
{
    int i;

    i = 0;
    while (table[i] != NULL)
        i++;
    return (i);
}

void    validate_extension(char *path)
{
    int size;

    size = ft_strlen(path) - 4;
    if (strcmp(".cub",path + size))
        app_error(4);
}

void    get_lists(int fd, t_game_data *data)
{
    char *line;
    t_game_params *params_list;
    t_map_line *lines_list;

    params_list = NULL;
    lines_list = NULL;
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
    if (line)
        app_error(1);
    data->params = params_list;
    data->lines = lines_list;
}

void    parse_map(char *path, t_game_data *data)
{
    int fd;
    char **map;

    validate_extension(path);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        app_error(5);
    // get_lists(fd, data);
    // validate_map(convert_lines_table(data->lines));
    // open the map and send fd to the appropriate function so it can get the game params.
}