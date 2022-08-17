#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;
    // t_map_list *temp;
    t_vars vars;
    t_img img;
    t_grid_data grid;
    //t_player player;


    grid.col = 0;
    grid.rect_height = 0;
    grid.row = 0;
    grid.rect_width = 0;
    grid.space_color =  0x00FFFFFF ;
    grid.wall_color = 0x002A0944;
    map = create_map_list (argv[1]);
    vars.mlx = mlx_init ();
    calculate_grid (map, &grid.rect_width, &grid.rect_height, &grid.col, &grid.row);
    printf ("%d %d \n", grid.col, grid.row);
    vars.mlx_win = mlx_new_window (vars.mlx, (grid.col * 32), (grid.row * 32), "CUB3D");
    img.img = mlx_new_image (vars.mlx, (grid.col * 32), (grid.row * 32));
    img.addr = mlx_get_data_addr (img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    draw_grid (map, grid, &img);
    mlx_put_image_to_window (vars.mlx, vars.mlx_win, img.img, 0,0);
    // temp = map;
    // while (temp)
    // {
    //     printf ("-->%s", temp->column);
    //     temp = temp->next;
    // }
    mlx_hook(vars.mlx_win, 2, 1L<<0, handle_keypress, &vars);
    mlx_loop (vars.mlx);
    return (0);
}