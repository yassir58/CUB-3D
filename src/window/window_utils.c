#include "../../includes/cub3d.h"


int	handle_keypress(int keycode, t_global_state *state)
{
    printf ("|%d|\n", keycode);
    if (keycode == XK_ESCAPE)
    {
        mlx_destroy_window(state->vars->mlx, state->vars->mlx_win);
        /// free allocated resources
        exit (EXIT_SUCCESS);
    }
    else if (keycode == XK_UP)
        move_player (UP, state);
    else if (keycode == XK_DOWN)
        move_player (DOWN, state);
    else if (keycode == XK_LEFT)
        move_player(LEFT, state);
    else if (keycode == XK_RIGHT)
        move_player(RIGHT, state);
    else if (keycode == R_LEFT)
        move_player (L, state);
    else if (keycode == R_RIGHT)
        move_player(R, state);
    else if (keycode == SHOOT)
        state->trigger = 1;
    else if (keycode == RELEAOD)
        state->releaod = 1;
    return (0);
}

int  handle_leave (t_global_state *state)
{
    /// free allocated resources
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
        play_sound (0);
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
        play_sound (1);
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