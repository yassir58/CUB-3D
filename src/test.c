#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;
    // t_map_list *temp;
    void *mlx;
    void *mlx_win;
    t_img img;
    t_grid_data grid;


    grid.col = 0;
    grid.rect_height = 0;
    grid.row = 0;
    grid.rect_width = 0;
    grid.space_color =  0x00FFFFFF  ;
    grid.wall_color = 0x00000000;
    map = create_map_list (argv[1]);
    mlx = mlx_init ();
    calculate_grid (map, &grid.rect_width, &grid.rect_height, &grid.col, &grid.row);
    printf ("%d %d \n", grid.col, grid.row);
    mlx_win = mlx_new_window (mlx, (grid.col * 32), (grid.row * 32), "CUB3D");
    img.img = mlx_new_image (mlx, (grid.col * 32), (grid.row * 32));
    img.addr = mlx_get_data_addr (img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    draw_grid (map, grid, &img);
    mlx_put_image_to_window (mlx, mlx_win, img.img, 0,0);
    // temp = map;
    // while (temp)
    // {
    //     printf ("-->%s", temp->column);
    //     temp = temp->next;
    // }
    mlx_loop (mlx);
    return (0);
}