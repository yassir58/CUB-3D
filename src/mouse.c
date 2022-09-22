/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:10 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 13:17:11 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int mouse_handle(int x, int y, void *param)
{
    t_global_state *state;
    int prevPos;
    int calculatedPos;

    (void)y;
    state = (t_global_state *)param;
    prevPos = state->data->prev_pos_mouse;
    calculatedPos = x - prevPos;
    if (calculatedPos < 0)
        state->player->v_angle -= 2;
    else
        state->player->v_angle += 2;
    rerender_map(state);
    state->data->prev_pos_mouse = x;
    return (0);
}