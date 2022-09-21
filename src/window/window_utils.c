#include "../../includes/cub3d.h"


int	handle_keypress(int keycode, t_global_state *state)
{
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
    // else if (keycode == SHOOT)
    // {
    //     printf ("%d \n", keycode);
    //     handle_sprite (state);
    // }
    return (0);
}

int  handle_leave (t_global_state *state)
{
    /// free allocated resources
    (void)state;
    exit (EXIT_SUCCESS);
    return (0);
}

void handle_sprite (t_global_state *state)
{
    rerender_sprite (state, state->sprites->pistol2);
    sleep (2);
    rerender_sprite (state, state->sprites->pistol3);
    sleep (2);
    rerender_sprite (state, state->sprites->pistol4);
    sleep (2);
    rerender_sprite (state, state->sprites->pistol5);
    sleep (1);
    rerender_sprite (state, state->sprites->pistol1);
    printf ("|tset|\n");
}