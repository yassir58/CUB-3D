#include "../../includes/cub3d.h"

int	handle_keypress(int keycode, t_global_state *state)
{
    if (keycode == XK_ESCAPE)
    {
        mlx_destroy_window(state->vars->mlx, state->vars->mlx_win);
        exit (EXIT_SUCCESS);
    }
    else if (keycode == XK_UP)
       state->move_up = 1;
    else if (keycode == XK_DOWN)
        state->move_down = 1;
    else if (keycode == XK_LEFT)
        state->move_left = 1;
    else if (keycode == XK_RIGHT)
        state->move_right = 1;
    else if (keycode == R_LEFT)
        state->rotate_left = 1;
    else if (keycode == R_RIGHT)
        state->rotate_right = 1;
    else if (keycode == SHOOT)
    {
        play_sound (0);
        state->trigger = 1;
    }
    else if (keycode == RELEAOD)
    {
        play_sound (1);
        state->releaod = 1;
    }
    return (0);
}

int handle_keyup  (int keycode, t_global_state *state)
{
    if (keycode == XK_UP)
       state->move_up = 0;
    else if (keycode == XK_DOWN)
        state->move_down = 0;
    else if (keycode == XK_LEFT)
        state->move_left = 0;
    else if (keycode == XK_RIGHT)
        state->move_right = 0;
    else if (keycode == R_LEFT)
        state->rotate_left = 0;
    else if (keycode == R_RIGHT)
        state->rotate_right = 0;
    return (0);
}

int handle_events (t_global_state *state)
{
     if (state->move_up)
        move_player (UP, state);
    if (state->move_down)
        move_player (DOWN, state);
    if (state->move_left)
        move_player(LEFT, state);
    if (state->move_right)
        move_player(RIGHT, state);
    if (state->rotate_left)
        move_player (L, state);
    if (state->rotate_right)
        move_player(R, state);
    handle_shoot_sprite (state);
    return (0);   
}

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


void init_hooks (t_global_state *state)
{
    mlx_hook(state->vars->mlx_win, 2, (1L<<0), handle_keypress, state);
    mlx_hook (state->vars->mlx_win, 3, (1L<<1), handle_keyup, state);
    mlx_hook (state->vars->mlx_win, LeaveNotify, 0, &handle_leave, state);
    mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle, state);
}