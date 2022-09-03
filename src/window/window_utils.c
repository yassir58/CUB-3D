#include "../../includes/cub3d.h"


int	handle_keypress(int keycode, t_global_state *state)
{
    printf("%d\n", keycode);
    if (keycode == XK_ESCAPE)
    {
        mlx_destroy_window(state->vars->mlx, state->vars->mlx_win);
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
        rotate_player (LEFT, state);
    else if (keycode == R_RIGHT)
        rotate_player (RIGHT, state);
    return (0);
}