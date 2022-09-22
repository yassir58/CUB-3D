#include "../includes/cub3d.h"


int main (int argc , char *argv[])
{
    (void)argc;
    // t_map_list *map;
    t_global_state *state;
   
    state = init_simulation_data(argv);
    init_window (state);
    init_game (state);
    raycaster(state);
    init_shoot_sprites (state);
    init_releaod_sprites (state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    state->current_sprite = state->sprites[0];
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->current_sprite.img.img, (state->data->window_width) - state->current_sprite.width, state->data->window_height -  state->current_sprite.height);
    mlx_hook(state->vars->mlx_win, 2, (1L<<0), handle_keypress, state);
    mlx_hook (state->vars->mlx_win, 3, (1L<<1), handle_keyup, state);
    mlx_hook (state->vars->mlx_win, LeaveNotify, 0, &handle_leave, state);
    mlx_hook(state->vars->mlx_win, 6, 0L, mouse_handle, state);
    mlx_loop_hook (state->vars->mlx, &handle_events, state);
    mlx_loop (state->vars->mlx);
    return (0);
}