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

int validate_map_hor_walls(char **map, int size)
{
    if (!wall_line(map[0]) || !wall_line(map[size - 1]))
        return (0);
    return (1);
}

int validate_player_position(char *line)
{
    //? If this function return 0 means that the player is in an incorrect position.
    if (ft_strchr(PLAYER_CHARS, line[0]) || ft_strchr(PLAYER_CHARS, line[ft_strlen(line) - 1]))
        return (0);
    return (1);
}

void    validate_map(char **map, int map_size)
{
    //  !Call the validate extension function here.
    //  ?This function will be reponsible for validating the the map.
    //  ?Validation:
    //      ?- The first line of the map cannot be a player so as the last line
    //      ?- The first character in everyline cannot be the player
    //      ?- The characters that are above or next to 0 should not be a space and that should take care of the map validation.

    if (validate_map_hor_walls(map, map_size))
    {
        printf("The map has valid horizontal walls\n");
    }
    else
    {
        printf("Error: invalid map parse error: validtion function\n");
        exit(1);
    }
    // Printing all the elements to see if the map has been sucessfully.
    // int i;
    // int size;

    // size = number_of_el(map);
    // i = 0;
    // while (i < size)
    // {
    //     printf("%s\n", map[i]);
    //     i++;
    // }
}