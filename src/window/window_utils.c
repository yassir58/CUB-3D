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

int  handle_leave (t_global_state *state)
{
    (void)state;
    exit (EXIT_SUCCESS);
    return (0);
}

int handle_shoot_sprite (t_global_state *state)
{
    static int i;
    static int j;
    
    if (state->trigger)
    {
        state->current_sprite = state->sprites[i++];
        rerender_map (state);
        if (i == 5)
        {
            state->trigger = 0;
            i = 0;
        }
    }
    else if (state->releaod)
    {
        state->current_sprite = state->releaod_sprites[j++];
        rerender_map (state);
        if (j == 10)
        {
            state->releaod = 0;
            j = 0;
            state->current_sprite = state->sprites[0];
            rerender_map (state);
        }
    }
    return (0);
}

void play_sound (int flag)
{
    int id;

    id = fork ();
    if (id == 0)
    {
        if (flag == 0)
            system ("afplay /Users/yelatman/Documents/CUB-3D/assets/shotgun-firing-4-6746.mp3");
        if (flag == 1)
            system ("afplay /Users/yelatman/Documents/CUB-3D/assets/1911-reload-6248.mp3");
        exit (EXIT_SUCCESS);
    }
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