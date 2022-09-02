#include "../../includes/cub3d.h"


int	handle_keypress(int keycode, t_vars *vars)
{
    printf("%d\n", keycode);
    if (keycode == XK_ESCAPE)
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit (EXIT_SUCCESS);
    }
    else if (keycode == XK_UP)
        move_player (UP);
    else if (keycode == XK_DOWN)
        move_player (DOWN);
    else if (keycode == XK_LEFT)
        move_player(LEFT);
    else if (keycode == XK_RIGHT)
        move_player(RIGHT);
    else if (keycode == R_LEFT)
        rotate_player (LEFT);
    else if (keycode == R_RIGHT)
        rotate_player (RIGHT);
    return (0);
}