#include "../includes/cub3d.h"

// int	ft_get_width(char *str, char sep)
// {
// 	int	i;
// 	int	words_count;

// 	i = 0;
// 	words_count = 0;
// 	if (str[i] != sep)
// 	{
// 		words_count += 1;
// 		i += 1;
// 	}
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != sep && str[i] != '\n' && str[i - 1] == sep)
// 			words_count++;
// 		i++;
// 	}
// 	return (words_count);
// }

// void	ft_get_dimensions(int fd, t_game_data *data)
// {
// 	char	*line;

// 	data->height = 0;
// 	line = get_next_line(fd);
// 	if (!line)
//     {
// 		printf("Error\n");
//         exit(1);
//     }
// 	data->width = ft_get_width(line, ' ');
// 	while (line != NULL)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		if (line)
// 		{
// 			if (data->width != ft_get_width(line, ' '))
//             {
//                 printf("Error\n");
//                 exit(1);
//             }
// 		}
// 		data->height++;
// 	}
// }

// void    get_game_info(char *path, t_game_data *data)
// {
//     int fd;
//     char *line;

//     fd = open(path, O_RDONLY);
//     if (fd < 0)
//         return ;
    
// }

int main(int argc, char **argv)
{
    t_game_data *data;

    data = (t_game_data *)malloc(sizeof(t_game_data));
    if (!data)
        return (0);
    if (argc > 1)
	    parse_map(argv[1], data);
    return (0);
}