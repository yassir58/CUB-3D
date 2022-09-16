#include "../includes/cub3d.h"


t_global_state *init_simulation_data(t_map_list *map)
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
    calculate_grid (map, &(data->grid->col), &(data->grid->row));
    init_player (data);
    data->data->map = get_map_vector (map, data);
    data->data->window_height = (RES_Y);
    data->data->window_width = (RES_X);
    data->data->prev_pos_mouse = 0;
    data->data->tileX = data->data->window_width / data->grid->col;
    data->data->tileY = data->data->tileX; 
    return (data);
}

void init_window (t_global_state *state)
{
    state->vars->mlx = mlx_init ();
    state->vars->mlx_win = mlx_new_window (state->vars->mlx, state->data->window_width * 2, state->data->window_height, "CUB3D");
    state->img.img = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_width);
    state->img.addr = (int *)mlx_get_data_addr (state->img.img, &(state->img.bits_per_pixel), &(state->img.line_length), &(state->img.endian));
}

char **get_map_vector (t_map_list *list, t_global_state *state)
{
    char **map_vector;
    t_map_list *tmp;
    int i;

    i = 0;
    tmp = list;
    map_vector = malloc (sizeof (char *) * (state->grid->row + 1));
    if (!map_vector)
        return (NULL);
    while (tmp)
    {
        map_vector[i] = ft_strdup (tmp->column);
        tmp = tmp->next;
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

void minimap_position (t_global_state *state)
{
    int i;
    int j;
    int x;
    int y;

    i = 0, j = 0, x = 0, y = 0;
    while (i < state->grid->row)
    {
        while (j < state->grid->col)
        {
            if (state->data->map[i][j] == 'P')
            {
                state->player->minimap_x = x + (MINIMAP_CEL / 2);
                state->player->minimap_y = y + (MINIMAP_CEL / 2);
            }
            x += MINIMAP_CEL;
            j++;
        }
        j = 0;
        x = 0;
        y += MINIMAP_CEL;
        i++;
    }
}

void init_player_position (t_global_state *state)
{
    int i;
    int j;
    int x;
    int y;

    i = 0, j = 0, x = 0, y = 0;
    while (i < state->grid->row)
    {
        while (j < state->grid->col)
        {
            if (state->data->map[i][j] == 'P')
            {
                state->player->initx = x + (state->data->tileX / 2);
                state->player->inity = y + (state->data->tileY / 2);
            }
            x += state->data->tileX;
            j++;
        }
        j = 0;
        x = 0;
        y += state->data->tileY ;
        i++;
    }
}


void init_game (t_global_state *state)
{
    init_player_position (state);
    // state->player->minimap_x = state->player->initx;
    // state->player->minimap_y = state->player->inity;
    minimap_position (state);
    load_texture_images (state);
    /// load texture images
}

void load_texture_images (t_global_state *state)
{
    state->north_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, "assets/north.xpm", &state->north_texture.width, &state->north_texture.height);
    state->north_texture.img.addr  = (int *)mlx_get_data_addr (state->north_texture.img.img, &(state->north_texture.img.bits_per_pixel), &(state->north_texture.img.line_length), &(state->north_texture.img.endian));   
    state->south_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, "assets/south.xpm", &state->south_texture.width, &state->south_texture.height);
    state->south_texture.img.addr  = (int *)mlx_get_data_addr (state->south_texture.img.img, &(state->south_texture.img.bits_per_pixel), &(state->south_texture.img.line_length), &(state->south_texture.img.endian));  
    state->west_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, "assets/west.xpm", &state->west_texture.width, &state->west_texture.height);
    state->west_texture.img.addr  = (int *)mlx_get_data_addr (state->west_texture.img.img, &(state->west_texture.img.bits_per_pixel), &(state->west_texture.img.line_length), &(state->west_texture.img.endian));  
    state->east_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, "assets/east.xpm", &state->east_texture.width, &state->east_texture.height);
    state->east_texture.img.addr  = (int *)mlx_get_data_addr (state->east_texture.img.img, &(state->east_texture.img.bits_per_pixel), &(state->east_texture.img.line_length), &(state->east_texture.img.endian));
}