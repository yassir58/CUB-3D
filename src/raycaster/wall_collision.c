/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:28 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/23 18:23:34 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int checkCoordinatesWall(double x, double y, t_global_state *state)
{
    double X;
    double Y;

    X = floor(x / state->data->tile_x);
    Y = floor(y / state->data->tile_y);
    if (!(X < state->grid->col && Y < state->grid->row))
        return (1);
    if (state->data->map[(int)Y][(int)X] == '1')
            return (1);
    return (0);
}

int checkCoordinatesWallTest(double x, double y, t_global_state *state, int flag)
{
    double X;
    double Y;
    int move_speed;

    move_speed = state->player->move_speed;
    X = floor(x / state->data->tile_x);
    Y = floor(y / state->data->tile_y);
    if (flag == UP && state->cast->distance_to_wall - move_speed  < 2)
            return (1);
    else if (flag == DOWN && state->cast->distance_to_wall + move_speed < 2)
            return (1);
    if (!(X > 0 && X < state->grid->col && Y > 0 && Y < state->grid->row))
        return (1);
    if (state->data->map[(int)Y][(int)X] == '1')
            return (1);
    return (0);
}
