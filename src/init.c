#include "../includes/cub3d.h"


t_global_state *init_simulation_data(char **argv)
{
    t_global_state *state;

    state = (t_global_state *)malloc(sizeof(t_global_state));
    if (!state)
        return (NULL);
    state->data = (t_game_data *)malloc(sizeof(t_game_data));
    state->grid = (t_grid_data *)malloc(sizeof(t_grid_data));
    state->player = (t_player *)malloc(sizeof(t_player));
    state->vars = (t_vars *)malloc(sizeof(t_vars));
    state->cast = (t_intersection_data *)malloc(sizeof(t_intersection_data));
    if (!state->data || !state->grid || !state->player || !state->vars || !state->cast)
        return (NULL);
    parse_map(argv[1], state);
    calculate_grid (state->data->map, &(state->grid->col), &(state->grid->row));
    init_player (state);
    state->data->window_height = (RES_Y);
    state->data->window_width = (RES_X);
    state->data->prev_pos_mouse = 0;
    state->data->tileX = state->data->window_width / state->grid->col;
    state->data->tileY = state->data->window_height / state->grid->row;
    state->data->prev_pos_mouse = state->data->window_width / 2;
    if (state->data->tileX < state->data->tileY)
        state->data->tileY = state->data->tileX;
    else
        state->data->tileX = state->data->tileY;
    return (state);
}

void init_window (t_global_state *state)
{
    state->vars->mlx = mlx_init ();
    state->vars->mlx_win = mlx_new_window (state->vars->mlx, state->data->window_width, state->data->window_height, "CUB3D");
    state->img.img = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_height);
    state->img.addr = (int *)mlx_get_data_addr (state->img.img, &(state->img.bits_per_pixel), &(state->img.line_length), &(state->img.endian));
    // testing

    // testing_img.img = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_height);
    // testing_img.addr = (int *)mlx_get_data_addr (testing_img.img, &(testing_img.bits_per_pixel), &(testing_img.line_length), &(testing_img.endian));
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

int get_angle(char direction)
{
    if (direction == 'N')
        return (270);
    else if (direction == 'S')
        return (90);
    else if (direction == 'E')
        return (360);
    else if (direction == 'W')
        return (180);
    else
        return (90);
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
    state->player->v_angle = get_angle(state->data->playerDirection);
    state->player->moveSpeed = 4;
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
            if (state->data->map[i][j] == state->data->playerDirection)
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
            if (state->data->map[i][j] == state->data->playerDirection)
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


void init_sprites (t_global_state *state)
{
    state->sprites->pistol1.img.img = mlx_xpm_file_to_image (state->vars->mlx, "assets/pistol1.xpm", &state->sprites->pistol1.width, &state->sprites->pistol1.height);
    state->sprites->pistol1.img.addr = (int *)mlx_get_data_addr (state->sprites->pistol1.img.img, &(state->sprites->pistol1.img.bits_per_pixel), &(state->sprites->pistol1.img.line_length), &(state->sprites->pistol1.img.endian));
    state->sprites->pistol2.img.img = mlx_xpm_file_to_image (state->vars->mlx, "assets/pistol2.xpm", &state->sprites->pistol2.width, &state->sprites->pistol2.height);
    state->sprites->pistol2.img.addr = (int *)mlx_get_data_addr (state->sprites->pistol2.img.img, &(state->sprites->pistol2.img.bits_per_pixel), &(state->sprites->pistol2.img.line_length), &(state->sprites->pistol2.img.endian));
    state->sprites->pistol3.img.img = mlx_xpm_file_to_image (state->vars->mlx, "assets/pistol3.xpm", &state->sprites->pistol3.width, &state->sprites->pistol3.height);
    state->sprites->pistol3.img.addr = (int *)mlx_get_data_addr (state->sprites->pistol3.img.img, &(state->sprites->pistol3.img.bits_per_pixel), &(state->sprites->pistol3.img.line_length), &(state->sprites->pistol3.img.endian));
    state->sprites->pistol4.img.img = mlx_xpm_file_to_image (state->vars->mlx, "assets/pistol4.xpm", &state->sprites->pistol4.width, &state->sprites->pistol4.height);
    state->sprites->pistol4.img.addr = (int *)mlx_get_data_addr (state->sprites->pistol4.img.img, &(state->sprites->pistol4.img.bits_per_pixel), &(state->sprites->pistol4.img.line_length), &(state->sprites->pistol4.img.endian));
    state->sprites->pistol5.img.img = mlx_xpm_file_to_image (state->vars->mlx, "assets/pistol5.xpm", &state->sprites->pistol5.width, &state->sprites->pistol5.height);
    state->sprites->pistol5.img.addr = (int *)mlx_get_data_addr (state->sprites->pistol5.img.img, &(state->sprites->pistol5.img.bits_per_pixel), &(state->sprites->pistol5.img.line_length), &(state->sprites->pistol5.img.endian));
    state->sprites->shotgun1.img.img = mlx_xpm_file_to_image (state->vars->mlx, "assets/shotgun1.xpm", &state->sprites->shotgun1.width, &state->sprites->shotgun1.height);
    state->sprites->shotgun1.img.addr = (int *)mlx_get_data_addr (state->sprites->shotgun1.img.img, &(state->sprites->shotgun1.img.bits_per_pixel), &(state->sprites->shotgun1.img.line_length), &(state->sprites->shotgun1.img.endian));
}