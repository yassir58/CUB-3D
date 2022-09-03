#include "../../includes/cub3d.h"


void move_player (int flag, t_global_state *state)
{
    int check;

    check = 0;
    if (flag == UP)
    {
        check  = check_for_wall (state->player->initx, 
        (state->player->inity - state->player->radius) - moveSpeed, state);
        if (state->player->inity - moveSpeed >= 0 && check)
            state->player->inity -= moveSpeed;
    }
    else if (flag == DOWN)
    {
        check = check_for_wall (state->player->initx, 
        (state->player->inity + state->player->radius) + moveSpeed, state);
        if (state->player->inity + moveSpeed <= RES_Y && check)
            state->player->inity += moveSpeed;
    }
    else if (flag == LEFT)
    {
        check = check_for_wall ((state->player->initx - state->player->radius) - moveSpeed,
        state->player->inity, state);
        if (state->player->initx - moveSpeed >= 0 && check)
            state->player->initx -= moveSpeed;
    }
    else if (flag == RIGHT)
    {
        check= check_for_wall ((state->player->initx) + moveSpeed,
        state->player->inity, state);
        if (state->player->initx + moveSpeed <= RES_X && check)
            state->player->initx += moveSpeed;
    }
    rerender_map (state);
}

void rerender_map (t_global_state *state)
{
    mlx_clear_window (state->vars->mlx, state->vars->mlx_win);
    draw_grid (state);
    draw_player (0x00FF0000, state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
}


void rotate_player (int direction, t_global_state *state)
{
    if (direction == LEFT)
    state->player->v_angle += rotationSpeed;
    else if (direction  == RIGHT)
    state->player->v_angle -= rotationSpeed;
    rerender_map (state);
}