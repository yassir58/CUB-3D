#include "../includes/cub3d.h"

int main (int argc , char *argv[])
{
    t_global_state *state;
   
    if (argc != 2)
    {
        perror ("Invalid arguments !");
        exit (EXIT_FAILURE);
    }
    state = init_simulation_data(argv);
    init_window (state);
    init_game (state);
    raycaster(state);
    init_shoot_sprites (state);
    init_releaod_sprites (state);
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->img.img, 0,0);
    state->current_sprite = state->sprites[0];
    mlx_put_image_to_window (state->vars->mlx, state->vars->mlx_win, state->current_sprite.img.img,
     (state->data->window_width) - state->current_sprite.width, state->data->window_height -  state->current_sprite.height);
    init_hooks (state);
    mlx_loop_hook (state->vars->mlx, &handle_events_2, state);
    mlx_loop (state->vars->mlx);
    return (0);
}