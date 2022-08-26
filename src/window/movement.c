#include "../../includes/cub3d.h"


void move_player (int flag)
{
    int check;


    if (flag == UP)
    {
        check  = check_for_wall (g_data.player.initx, 
        (g_data.player.inity - g_data.player.radius) - moveSpeed);
        if (g_data.player.inity - moveSpeed >= 0 && check)
            g_data.player.inity -= moveSpeed;
    }
    else if (flag == DOWN)
    {
        check = check_for_wall (g_data.player.initx, 
        (g_data.player.inity + g_data.player.radius) + moveSpeed);
        if (g_data.player.inity + moveSpeed <= RES_Y && check)
            g_data.player.inity += moveSpeed;
    }
    else if (flag == LEFT)
    {
        check = check_for_wall ((g_data.player.initx - g_data.player.radius) - moveSpeed,
        g_data.player.inity);
        if (g_data.player.initx - moveSpeed >= 0 && check)
            g_data.player.initx -= moveSpeed;
    }
    else if (flag == RIGHT)
    {
        check= check_for_wall ((g_data.player.initx) + moveSpeed,
        g_data.player.inity);
        if (g_data.player.initx + moveSpeed <= RES_X && check)
            g_data.player.initx += moveSpeed;
    }
    rerender_map ();
}

void rerender_map ()
{
    mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
    draw_grid ();
    draw_player (0x00FF0000);
    mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
}


void rotate_player (int direction)
{
    if (direction == LEFT)
        g_data.player.v_angle += rotationSpeed;
    else if (direction  == RIGHT)
        g_data.player.v_angle -= rotationSpeed;
    rerender_map ();
}