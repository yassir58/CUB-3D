#include "../../includes/cub3d.h"


void move_player_up (void)
{
    int c;

    c =  check_for_wall (g_data.player.initx , g_data.player.inity - moveSpeed);
    if (check_outside_map (0) && c != '1')
    {
        g_data.player.inity -= moveSpeed;
        mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
        draw_grid ();
        draw_player (g_data.player.initx, g_data.player.inity, g_data.player.radius, 0x00FF0000);
        mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
    }
}

void move_player_down (void)
{
    int c;

    c = check_for_wall (g_data.player.initx, g_data.player.inity + moveSpeed);
    if (check_outside_map (1) && c != '1')
    {
        g_data.player.inity += moveSpeed;
        mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
        draw_grid ();
        draw_player (g_data.player.initx, g_data.player.inity, g_data.player.radius, 0x00FF0000);
        mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
    }
}

void move_player_left (void)
{
    int c;

    c = check_for_wall (g_data.player.initx - moveSpeed, g_data.player.inity);
    if (check_outside_map (2) && c != '1')
    {
        g_data.player.initx -= moveSpeed;
        mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
        draw_grid ();
        draw_player (g_data.player.initx, g_data.player.inity, g_data.player.radius, 0x00FF0000);
        mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
    }
}
void move_player_right (void)
{
    int c;

    c = check_for_wall (g_data.player.initx + moveSpeed, g_data.player.inity);
    if (check_outside_map (3) && c != '1')
    {
        g_data.player.initx += moveSpeed;
        mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
        draw_grid ();
        draw_player (g_data.player.initx, g_data.player.inity, g_data.player.radius, 0x00FF0000);
        mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
    }
}

int check_outside_map (int flag)
{
    int res;

    res = 0;
    if (flag == 0)
    {
        if (g_data.player.inity - moveSpeed - g_data.player.radius > 0)
            res = 1;
    }
    else if (flag == 1)
    {
        if (g_data.player.inity + moveSpeed + (g_data.player.radius * 2) < g_data.data.height)
            res = 1;
    }
    else if (flag == 2)
    {
        if (g_data.player.initx - moveSpeed - g_data.player.radius > 0)
            res = 1;
    }
    else if (flag == 3)
    {
        if (g_data.player.initx + moveSpeed + (g_data.player.radius * 2) < g_data.data.width)
            res = 1;
    }
    return (res);
}