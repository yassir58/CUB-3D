#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;
    t_global_state *state;
   
    map = create_map_list (argv[1]);
    state = init_simulation_data();
    init_window (map, state);
    texture_img.img =  mlx_xpm_file_to_image (state->vars->mlx, "assets/eagle.xpm", &w, &h);
    printf ("w %d h %d \n", w, h);
    texture_img.addr  = (int *)mlx_get_data_addr (texture_img.img, &(texture_img.bits_per_pixel), &(texture_img.line_length), &(texture_img.endian));
    testing_img.img = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_height);
    testing_img.addr = (int *)mlx_get_data_addr (testing_img.img, &(testing_img.bits_per_pixel), &(testing_img.line_length), &(testing_img.endian));
    draw_grid (state);
    raycaster(state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, testing_img.img,state->data->window_width,0);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    mlx_hook(state->vars->mlx_win, 2, 1L<<0, handle_keypress, state);
    mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle, state);
    mlx_loop (state->vars->mlx);
    return (0);
}