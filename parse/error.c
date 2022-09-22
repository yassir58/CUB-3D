/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:28 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 13:21:11 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	else if (code == 11)
		printf("Error: missing identifiers.\n");
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
