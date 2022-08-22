#include "../../includes/cub3d.h"


int	handle_keypress(int keycode, t_vars *vars)
{
    if (keycode == XK_ESCAPE)
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit (EXIT_SUCCESS);
    }
    else if (keycode == XK_UP)
        move_player_up ();
    else if (keycode == XK_DOWN)
        move_player_down ();
    else if (keycode == XK_LEFT)
        move_player_left ();
    else if (keycode == XK_RIGHT)
        move_player_right ();
    return (0);
}


