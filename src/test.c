#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;

    map = create_map_list (argv[1]);
    init_window (map);
    draw_grid ();
    mlx_put_image_to_window (g_data.vars.mlx, g_data.vars.mlx_win, g_data.img.img, 0,0);
    // mlx_hook(g_data.vars.mlx_win, 2, 1L<<0, handle_keypress, &(g_data.vars));
    mlx_loop (g_data.vars.mlx);
    return (0);
}