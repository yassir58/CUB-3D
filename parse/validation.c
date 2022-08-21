#include "../includes/cub3d.h"

int wall_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (strchr(WALL_LINE, line[i]))
            return (1);
        i++;
    }
    return (0);
}

int line_contain_player(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (strchr(PLAYER_CHARS, line[i]))
            return (1);
        i++;
    }
    return (0);
}

void    validate_map(char **map)
{
    //  ?This function will be reponsible for validating the the map.
    //  ?Validation:
    //      ?- The first line of the map cannot be a player so as the last line
    //      ?- The first character in everyline cannot be the player
    //      ?- The characters that are above or next to 0 should not be a space and that should take care of the map validation.


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