#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;
    t_global_state *state;
   
    map = create_map_list (argv[1]);
    state = init_simulation_data();
    init_window (map, state);
    draw_grid (state); 
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    mlx_hook(state->vars->mlx_win, 2, 1L<<0, handle_keypress, state);
    mlx_loop (state->vars->mlx);
    return (0);
}