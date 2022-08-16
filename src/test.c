#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;
    // t_map_list *temp;
    void *mlx;
    void *mlx_win;
   t_img img;

    
    mlx = mlx_init ();
    mlx_win = mlx_new_window (mlx, RES_X, RES_Y, "CUB3D");
    map = create_map_list (argv[1]);
    img.img = mlx_new_image (mlx, RES_X, RES_Y);
    img.addr = mlx_get_data_addr (img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    my_mlx_pixel_put (&img , 5, 5, 0x00FF0000);
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