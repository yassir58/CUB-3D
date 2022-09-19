#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    // t_map_list *map;
    t_global_state *state;
   
    state = init_simulation_data(argv);
    init_window (state);
    init_game (state);
    // draw_grid (state);
    // draw_player (0x00FF0145,state);
    raycaster(state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    //  mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, testing_img.img, 0,0);
    mlx_hook(state->vars->mlx_win, 2, 1L<<0, handle_keypress, state);
    mlx_hook (state->vars->mlx_win, LeaveNotify, 0, &handle_leave, state);
    mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle, state);
    mlx_loop (state->vars->mlx);
    return (0);
}