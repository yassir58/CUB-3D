#include "../includes/cub3d.h"





int main (int argc , char *argv[])
{
    (void)argc;
    t_map_list *map;
    t_global_state *state;
   
    map = create_map_list (argv[1]);
    state = init_simulation_data(map);
    init_window (state);
    init_game (state);
    // draw_grid (state);
    // draw_player (0x00FF0145,state);
    raycaster(state);
    init_sprites (state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    // state->current_sprite = state->sprites->pistol1;
    // mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->sprites->pistol1.img.img, state->data->window_width - state->sprites->pistol1.width, state->data->window_height -  state->sprites->pistol1.height);
    mlx_hook(state->vars->mlx_win, 2, 1L<<0, handle_keypress, state);
    mlx_hook (state->vars->mlx_win, LeaveNotify, 0, &handle_leave, state);
    mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle, state);
    mlx_loop (state->vars->mlx);
    return (0);
}