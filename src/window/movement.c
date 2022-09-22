/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:54 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 13:16:55 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    correctPlayerAngle(t_global_state *state)
{
    if (state->player->v_angle < 0)
        state->player->v_angle += 360;
    else if (state->player->v_angle > 360)
        state->player->v_angle = state->player->v_angle % 360;
}


void move_player (int flag, t_global_state *state)
{
    double newPlayerX;
    double newPlayerY;
    int moveDirection;
    int rotationDirection;

    rotationDirection = 0;
    moveDirection = 0;
    if (flag == UP)
        moveDirection = 1;
    else if (flag == DOWN)
        moveDirection = -1;
    else if (flag == RIGHT)
    {
        newPlayerX = state->player->initx - state->player->moveSpeed * sin(deg_to_radian(state->player->v_angle));
        newPlayerY = state->player->inity + state->player->moveSpeed * cos(deg_to_radian(state->player->v_angle));
        if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
        {
            state->player->initx = newPlayerX;
            state->player->inity = newPlayerY;
        }
        return (rerender_map(state));
    }
    else if (flag == LEFT)
    {
        newPlayerX = state->player->initx + state->player->moveSpeed * sin(deg_to_radian(state->player->v_angle));
        newPlayerY = state->player->inity - state->player->moveSpeed * cos(deg_to_radian(state->player->v_angle));
        if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
        {
            state->player->initx = newPlayerX;
            state->player->inity = newPlayerY;
        }
        return (rerender_map(state));
    }
    else if (flag == L)
        rotationDirection = -1;
    else if (flag == R)
        rotationDirection = 1;
    state->player->v_angle += rotationDirection * rotationSpeed;
    correctPlayerAngle(state);
    newPlayerX = state->player->initx + (moveDirection * state->player->moveSpeed) * cos(deg_to_radian(state->player->v_angle));
    newPlayerY = state->player->inity + (moveDirection * state->player->moveSpeed) * sin(deg_to_radian(state->player->v_angle));
    if (!checkCoordinatesWallTest(newPlayerX, newPlayerY, state, flag))
    {
        state->player->initx = newPlayerX;
        state->player->inity = newPlayerY;
    }
    rerender_map (state);
}

// void move_player (int flag, t_global_state *state)
// {
//     int check;

//     check = 0;
//     if (flag == UP)
//     {
//         check  = check_for_wall (state->player->initx, 
//         (state->player->inity - state->player->radius) - state->player->moveSpeed, state);
//         if (state->player->inity - state->player->moveSpeed >= 0 && check)
//             state->player->inity -= state->player->moveSpeed;
//     }
//     else if (flag == DOWN)
//     {
//         check = check_for_wall (state->player->initx, 
//         (state->player->inity + state->player->radius) + state->player->moveSpeed, state);
//         if (state->player->inity + state->player->state->player->moveSpeed <= RES_Y && check)
//             state->player->inity += state->player->moveSpeed;
//     }
//     else if (flag == LEFT)
//     {
//         check = check_for_wall ((state->player->initx - state->player->radius) - state->player->moveSpeed,
//         state->player->inity, state);
//         if (state->player->initx - state->player->moveSpeed >= 0 && check)
//             state->player->initx -= state->player->moveSpeed;
//     }
//     else if (flag == RIGHT)
//     {
//         check= check_for_wall ((state->player->initx) + state->player->moveSpeed,
//         state->player->inity, state);
//         if (state->player->initx + state->player->moveSpeed <= RES_X && check)
//             state->player->initx += state->player->moveSpeed;
//     }
//     rerender_map (state);
// }

void rerender_map (t_global_state *state)
{
    mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
    raycaster (state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
}

void rerender_sprite (t_global_state *state, t_texture sprite)
{
    mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
    raycaster (state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, sprite.img.img, state->data->window_width - sprite.width, state->data->window_height -  sprite.height);
}

// void rotate_player (int direction, t_global_state *state)
// {
//     if (direction == LEFT)
//     state->player->v_angle -= rotationSpeed;
//     else if (direction  == RIGHT)
//     state->player->v_angle += rotationSpeed;
//     rerender_map (state);
// }