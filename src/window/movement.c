#include "../../includes/cub3d.h"

/*
void move_player_up (void)
{
    check_for_wall (g_data.player.initx, g_data.player.inity - (moveSpeed), UP);
    g_data.player.inity -= moveSpeed;
    mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
    draw_grid ();
    draw_player ( 0x00FF0000);
    mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
}

void move_player_down (void)
{
    check_for_wall (g_data.player.initx, g_data.player.inity + (moveSpeed), DOWN);
    g_data.player.inity += moveSpeed;
    mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
    draw_grid ();
    draw_player (0x00FF0000);
    mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
}

void move_player_left (void)
{ 
    check_for_wall (g_data.player.initx - (moveSpeed), g_data.player.inity , LEFT);
    g_data.player.initx -= moveSpeed;
    mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
    draw_grid ();
    draw_player (0x00FF0000);
    mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
}
void move_player_right (void)
{
    check_for_wall (g_data.player.initx + (moveSpeed), g_data.player.inity, RIGHT);
    g_data.player.initx += moveSpeed;
    mlx_clear_window (g_data.vars.mlx, g_data.vars.mlx_win);
    draw_grid ();
    draw_player (0x00FF0000);
    mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
}

void draw_line (int start_x, int start_y, int end_x, int end_y)
{
    int dx, dy, p, x, y;
 
    dx = end_x - start_x;
    dy = end_y - start_y;
 
    x= start_x;
    y= start_y; 
    p=2 * (dy-dx);
 
    while(x < end_x)
    {
        if(p >= 0)
        {
            my_mlx_pixel_put (&g_data.img, x, y, 0x00FF0000);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            my_mlx_pixel_put (&g_data.img, x, y, 0x00FF0000);
            p=p+2*dy;
        }
        x=x+1;
    }
}
*/