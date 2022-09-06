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
    else if (flag == L)
        rotationDirection = -1;
    else if (flag == R)
        rotationDirection = 1;
    state->player->v_angle += rotationDirection * rotationSpeed;
    correctPlayerAngle(state);
    newPlayerX = state->player->initx + (moveDirection * moveSpeed) * cos(deg_to_radian(state->player->v_angle));
    newPlayerY = state->player->inity + (moveDirection * moveSpeed) * sin(deg_to_radian(state->player->v_angle));
    if (!checkCoordinatesWall(newPlayerX, newPlayerY, state))
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
//         (state->player->inity - state->player->radius) - moveSpeed, state);
//         if (state->player->inity - moveSpeed >= 0 && check)
//             state->player->inity -= moveSpeed;
//     }
//     else if (flag == DOWN)
//     {
//         check = check_for_wall (state->player->initx, 
//         (state->player->inity + state->player->radius) + moveSpeed, state);
//         if (state->player->inity + moveSpeed <= RES_Y && check)
//             state->player->inity += moveSpeed;
//     }
//     else if (flag == LEFT)
//     {
//         check = check_for_wall ((state->player->initx - state->player->radius) - moveSpeed,
//         state->player->inity, state);
//         if (state->player->initx - moveSpeed >= 0 && check)
//             state->player->initx -= moveSpeed;
//     }
//     else if (flag == RIGHT)
//     {
//         check= check_for_wall ((state->player->initx) + moveSpeed,
//         state->player->inity, state);
//         if (state->player->initx + moveSpeed <= RES_X && check)
//             state->player->initx += moveSpeed;
//     }
//     rerender_map (state);
// }

void rerender_map (t_global_state *state)
{
    mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
    draw_grid (state);
    draw_player (0x00FF0000, state);
    raycaster(state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
}


// void rotate_player (int direction, t_global_state *state)
// {
//     if (direction == LEFT)
//     state->player->v_angle -= rotationSpeed;
//     else if (direction  == RIGHT)
//     state->player->v_angle += rotationSpeed;
//     rerender_map (state);
// }