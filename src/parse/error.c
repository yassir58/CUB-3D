/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:28 by ochoumou          #+#    #+#             */
/*   Updated: 2022/10/09 11:03:18 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	app_error(int code)
{
	if (code == 1)
		printf("Error: parse error: invalid map.\n");
	else if (code == 2)
		printf("Error: invalid map.\n");
	else if (code == 3)
		printf("Error: map colors are incorrect.\n");
	else if (code == 4)
		printf("Error: invalid map or texture extension.\n");
	else if (code == 5)
		printf("Error: could not open file, error reading the file.\n");
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
	else if (code == 11)
		printf("Error: missing identifiers. or duplicated identifer\n");
	else if (code == 12)
		printf("Error: empty file or file does not exist.\n");
	exit(1);
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	check_map_file(char *path)
{
	int		fd;
	char	buff[1];

	buff[0] = 0;
	fd = open(path, O_RDONLY);
	validate_extension(path, ".cub");
	read(fd, buff, 1);
	if (buff[0] == 0)
		app_error(12);
	close(fd);
	if (fd < 0)
		app_error(5);
}

int	check_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
