#include "../includes/cub3d.h"

int wall_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!strchr(WALL_LINE, line[i]))
            return (0);
        i++;
    }
    return (1);
}


int validate_map_line(char *line, char *prevline, char *nextline)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '0')
        {
            if (!((line[i - 1] && line[i - 1] != ' ') && (line[i + 1] && line[i + 1 != ' ']) && (prevline[i] && prevline[i] != ' ') && (nextline[i] && nextline[i] != ' ')))
                app_error(8);
        }
        i += 1;
    }
    return (0);
}

int validate_map_hor_walls(char **map, int size)
{
    if (!wall_line(map[0]) || !wall_line(map[size - 1]))
        return (0);
    return (1);
}

void validate_player_occurrence(char **map)
{
    bool player;
    int i;
    int j;

    i = 0;
    j = 0;
    player = false;
    while (map[i])
    {
        while (map[i][j] != '\0')
        {
            if (ft_strchr(PLAYER_CHARS, map[i][j]) && !player)
                player = true;
            else if (ft_strchr(PLAYER_CHARS, map[i][j]) && player)
                app_error(9);
            j++;
        }
        j = 0;
        i++;
    }
    if (!player)
        app_error(10);
}

void validate_player_position(char *line)
{
    if (ft_strchr(PLAYER_CHARS, line[0]) || ft_strchr(PLAYER_CHARS, line[ft_strlen(line) - 1]))
        app_error(7);
}

char    **validate_map(char **map, int map_size)
{
    int i;
    
    i = 1;
    //  !Call the validate extension function here.
    //  ?This function will be reponsible for validating the the map.
    //  ?Validation:
    //      ?- The first line of the map cannot be a player so as the last line
    //      ?- The first character in everyline cannot be the player
    //      ?- The characters that are above or next to 0 should not be a space and that should take care of the map validation.
    //      ?- Check that the player only exit once in the map.
    if (validate_map_hor_walls(map, map_size))
    {
        validate_player_occurrence(map);
        while (i < map_size - 1)
        {
            validate_player_position(map[i]);
            validate_map_line(map[i], map[i - 1], map[i + 1]);
            i += 1;
        }
    }
    else
    {
        printf("Error: invalid map parse error: validtion function\n");
        exit(1);
    }
    return (map);
}