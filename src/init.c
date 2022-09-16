#include "../includes/cub3d.h"


t_global_state *init_simulation_data(void)
{
    t_global_state *data;

    data = (t_global_state *)malloc(sizeof(t_global_state));
    if (!data)
        return (NULL);
    data->data = (t_game_data *)malloc(sizeof(t_game_data));
    data->grid = (t_grid_data *)malloc(sizeof(t_grid_data));
    data->player = (t_player *)malloc(sizeof(t_player));
    data->vars = (t_vars *)malloc(sizeof(t_vars));
    if (!data->data || !data->grid || !data->player || !data->vars)
        return (NULL);
    return (data);
}

void init_window (t_map_list *map, t_global_state *state)
{
    state->vars->mlx = mlx_init ();
    calculate_grid (map, &(state->grid->col), &(state->grid->row));
    init_player (state);
    state->data->window_height = (RES_Y);
    state->data->window_width = (RES_X);
    state->data->prev_pos_mouse = 0;
    state->data->tileX = state->data->window_width / state->grid->col;
    // state->data->tileY = state->data->window_height / state->grid->row;
    state->data->tileY = state->data->tileX; 
    state->vars->mlx_win = mlx_new_window (state->vars->mlx, state->data->window_width * 2, state->data->window_height, "CUB3D");
    printf ("res_x %d res_y %d \n", state->data->window_width, state->data->window_height);
    state->img.img = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_width);
    state->img.addr = (int *)mlx_get_data_addr (state->img.img, &(state->img.bits_per_pixel), &(state->img.line_length), &(state->img.endian));
    state->data->map = get_map_vector (map, state);
}

char **get_map_vector (t_map_list *list, t_global_state *state)
{
    char **map_vector;
    t_map_list *tmp;
    // t_map_list *ptr;
    int i;

    i = 0;
    tmp = list;
    map_vector = malloc (sizeof (char *) * (state->grid->row + 1));
    if (!map_vector)
        return (NULL);
    while (tmp)
    {
        // ptr = tmp;
        map_vector[i] = ft_strdup (tmp->column);
        tmp = tmp->next;
        // free (tmp);
        i++;
    }
    map_vector[i] = NULL;
    return (map_vector);
}


void init_player (t_global_state *state)
{
    state->player->initx = 0;
    state->player->inity = 0;
    state->player->radius = 2;
    state->player->turnDirection = 0;
    state->player->walkDirection = 0;
    state->player->x_cord = 0;
    state->player->y_cord = 0;
    state->player->d_x = 0;
    state->player->d_y = 0;
    state->player->d_length = 50;
    state->player->v_angle = E;
}