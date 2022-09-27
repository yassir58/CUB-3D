/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:59:48 by yelatman          #+#    #+#             */
/*   Updated: 2022/09/27 11:37:49 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_global_state	*state;

	if (argc != 2)
	{
		perror ("Invalid arguments !");
		exit (EXIT_FAILURE);
	}
	state = init_simulation_data (argv);
	init_window (state);
	init_game (state);
	raycaster(state);
	mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win,
		state->img.img, 0, 0);
	init_hooks (state, 1);
	mlx_loop_hook (state->vars->mlx, &handle_events, state);
	mlx_loop (state->vars->mlx);
	return (0);
}
