#include "../includes/cub3d.h"

void    app_error(int code)
{
    //! In this function we should free all the allocated lists before exit.
    if (code == 1)
        printf("Error: parse error: invalid map.\n");
    else if (code == 2)
        printf("Error: invalid map.\n");
    else if (code == 3)
        printf("Error: map colors are incorrect.\n");
    else if (code == 4)
        printf("Error: invalid map extension.\n");
    else if (code == 5)
        printf("Error: could not open file.\n");
    else if (code == 6)
        printf("Error: invalid identifer\n");
    else if (code == 7)
        printf("Error: invalid player position.\n");
    else if (code == 8)
        printf("Error: invalid map structure.\n");
    else if (code == 9)
        printf("Error: player exists in multiple places.\n");
     else if (code == 10)
        printf("Error: player does not exist.\n");
    exit(1);
}

// !TODO: 
//     + Validate the map extension.
//     + Check that every texture file exits if its not return an error.
//     + Check the order of the elements according to the map

int check_identifier(char *id)
{
    if (!ft_strcmp(id, "NO") || !ft_strcmp(id, "SO") || !ft_strcmp(id, "WE") || !ft_strcmp(id, "EA"))
        return (1);
    else if (!ft_strcmp(id, "F") || !ft_strcmp(id, "C"))
        return (2);
    return (0);
}

int get_identifer_number(char *id)
{
    if (!ft_strcmp(id, "NO"))
        return (1);
    else if (!ft_strcmp(id, "SO"))
        return (2);
    else if (!ft_strcmp(id, "WE"))
        return (3);
    else if (!ft_strcmp(id, "EA"))
        return (4);
    else if (!ft_strcmp(id, "F"))
        return (5);
    else if (!ft_strcmp(id, "C"))
        return (6);
    return (0);
}

void check_identifers_order(t_game_params *params)
{
    t_game_params *tmp;

    tmp = params;
    while (tmp->next != NULL)
    {
        if (tmp->index < tmp->next->index)
            tmp = tmp->next;
        else
            app_error(6);
    }
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
    
    // printf("%s\n", str);
    rgb = ft_split(str, ',');
    color = 0;
    if (count_seperator(str, ',') == 2)
    {
        if (ft_atoi(rgb[0]) <= 255 && ft_atoi(rgb[1]) <= 255 && ft_atoi(rgb[2]) <= 255)
        {
            // printf("Blue: %d\n",ft_atoi(rgb[0]));
            // printf("Green: %d\n",ft_atoi(rgb[1]));
            // printf("Red: %d\n",ft_atoi(rgb[2]));
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
    // 
    // TODO: I think that i should validate the key according to the attributes mentioned in the subject.
    splitted = get_key_value(line);
    if (ft_strlen(splitted[0]) && ft_strlen(splitted[1]))
    {
        key = splitted[0];
        value = splitted[1];
        if (!search_params_list(key, params_list))
        {
            if (check_identifier(key) == 2)
            {
                //! Memory Leak.
                color = get_color(value);
                if (color == -1)
                    app_error(3);
                value = ft_itoa(color);
            }
            else if (check_identifier(key) == 1)
                check_path(value);
            else
                app_error(6);
            add_param(params_list, new_params(key, value, get_identifer_number(key)));
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
    // !Should close the fd here to not leak file descriptors.
}

void    parse_map(char *path, t_game_data *data)
{
    int fd;
    char **map;

    validate_extension(path);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        app_error(5);
    get_lists(fd, data);
    print_params_list(data->params);
    check_identifers_order(data->params);
    validate_map(convert_lines_table(data->lines), lines_number(data->lines));
    // open the map and send fd to the appropriate function so it can get the game params.
}