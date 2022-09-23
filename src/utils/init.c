#include "../../includes/cub3d.h"


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
    state->cast = (t_raycast *)malloc(sizeof(t_raycast));
    if (!state->data || !state->grid || !state->player || !state->vars || !state->cast)
        return (NULL);
    parse_map(argv[1], state);
    calculate_grid (state->data->map, &(state->grid->col), &(state->grid->row));
    state->data->window_height = (RES_Y);
    state->data->window_width = (RES_X);
    state->data->tileX = state->data->window_width / state->grid->col;
    state->data->tileY = state->data->window_height / state->grid->row;
    state->data->prev_pos_mouse = state->data->window_width / 2;
    state->speed_factor = state->data->window_width /  (state->grid->col * state->grid->row);
    init_player (state);
    if (state->data->tileX < state->data->tileY)
        state->data->tileY = state->data->tileX;
    else
        state->data->tileX = state->data->tileY;
    return (state);
}

void init_window (t_global_state *state)
{
    state->vars->mlx = mlx_init ();
    state->vars->mlx_win = mlx_new_window (state->vars->mlx, state->data->window_width, state->data->window_height, "Insurgency: Sandstorm");
    state->img.img = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_height);
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
    if (state->speed_factor == 0)
        state->player->moveSpeed = 1;
    else
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
    minimap_position (state);
    load_texture_images (state);
}

void load_texture_images (t_global_state *state)
{
    t_game_params *tmp;

    tmp = state->data->params;
    while (tmp)
    {
        if (!ft_strcmp (tmp->key, "NO"))
        {
            state->north_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, tmp->value, &state->north_texture.width, &state->north_texture.height);
            state->north_texture.img.addr  = (int *)mlx_get_data_addr (state->north_texture.img.img, &(state->north_texture.img.bits_per_pixel), &(state->north_texture.img.line_length), &(state->north_texture.img.endian));
        }
        else if (!ft_strcmp (tmp->key, "SO"))
        {
            state->south_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, tmp->value, &state->south_texture.width, &state->south_texture.height);
            state->south_texture.img.addr  = (int *)mlx_get_data_addr (state->south_texture.img.img, &(state->south_texture.img.bits_per_pixel), &(state->south_texture.img.line_length), &(state->south_texture.img.endian));  
        }
        else if (!ft_strcmp (tmp->key, "WE"))
        {
            state->west_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, tmp->value, &state->west_texture.width, &state->west_texture.height);
            state->west_texture.img.addr  = (int *)mlx_get_data_addr (state->west_texture.img.img, &(state->west_texture.img.bits_per_pixel), &(state->west_texture.img.line_length), &(state->west_texture.img.endian));  
        }
        else if (!ft_strcmp (tmp->key, "EA"))
        {
            state->east_texture.img.img =  mlx_xpm_file_to_image (state->vars->mlx, tmp->value, &state->east_texture.width, &state->east_texture.height);
            state->east_texture.img.addr  = (int *)mlx_get_data_addr (state->east_texture.img.img, &(state->east_texture.img.bits_per_pixel), &(state->east_texture.img.line_length), &(state->east_texture.img.endian));
        }
        else if (!ft_strcmp (tmp->key, "C"))
            state->data->ceil = ft_atoi (tmp->value);
        else if (!ft_strcmp (tmp->key, "F"))
            state->data->floor = ft_atoi (tmp->value);
        tmp = tmp->next;
    }
}

void init_shoot_sprites (t_global_state *state)
{
    state->sprites = malloc (sizeof (t_texture) * 15); 

    state->sprites[0].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr1.xpm", &state->sprites[0].width, &state->sprites[0].height);
    state->sprites[0].img.addr = (int *)mlx_get_data_addr (state->sprites[0].img.img, &state->sprites[0].img.bits_per_pixel, &state->sprites[0].img.line_length, &state->sprites[0].img.endian);
    state->sprites[1].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr2.xpm", &state->sprites[1].width, &state->sprites[1].height);
    state->sprites[1].img.addr = (int *)mlx_get_data_addr (state->sprites[1].img.img, &state->sprites[1].img.bits_per_pixel, &state->sprites[1].img.line_length, &state->sprites[1].img.endian);
    state->sprites[2].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr3.xpm", &state->sprites[2].width, &state->sprites[2].height);
    state->sprites[2].img.addr = (int *)mlx_get_data_addr (state->sprites[2].img.img, &state->sprites[2].img.bits_per_pixel, &state->sprites[2].img.line_length, &state->sprites[2].img.endian);
    state->sprites[3].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr4.xpm", &state->sprites[3].width, &state->sprites[3].height);
    state->sprites[3].img.addr = (int *)mlx_get_data_addr (state->sprites[3].img.img, &state->sprites[3].img.bits_per_pixel, &state->sprites[3].img.line_length, &state->sprites[3].img.endian);
    state->sprites[4].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr5.xpm", &state->sprites[4].width, &state->sprites[4].height);
    state->sprites[4].img.addr = (int *)mlx_get_data_addr (state->sprites[4].img.img, &state->sprites[4].img.bits_per_pixel, &state->sprites[4].img.line_length, &state->sprites[4].img.endian);
    state->sprites[5].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr6.xpm", &state->sprites[5].width, &state->sprites[5].height);
    state->sprites[5].img.addr = (int *)mlx_get_data_addr (state->sprites[5].img.img, &state->sprites[5].img.bits_per_pixel, &state->sprites[5].img.line_length, &state->sprites[5].img.endian);
    state->sprites[6].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr7.xpm", &state->sprites[6].width, &state->sprites[6].height);
    state->sprites[6].img.addr = (int *)mlx_get_data_addr (state->sprites[6].img.img, &state->sprites[6].img.bits_per_pixel, &state->sprites[6].img.line_length, &state->sprites[6].img.endian);
}

void init_releaod_sprites (t_global_state *state)
{
    state->releaod_sprites = malloc (sizeof (t_texture) * 15); 


    state->releaod_sprites[0].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr8.xpm", &state->releaod_sprites[0].width, &state->releaod_sprites[0].height);
    state->releaod_sprites[0].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[0].img.img, &state->releaod_sprites[0].img.bits_per_pixel, &state->releaod_sprites[0].img.line_length, &state->releaod_sprites[0].img.endian);
    state->releaod_sprites[1].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr9.xpm", &state->releaod_sprites[1].width, &state->releaod_sprites[1].height);
    state->releaod_sprites[1].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[1].img.img, &state->releaod_sprites[1].img.bits_per_pixel, &state->releaod_sprites[1].img.line_length, &state->releaod_sprites[1].img.endian);
    state->releaod_sprites[2].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr10.xpm", &state->releaod_sprites[2].width, &state->releaod_sprites[2].height);
    state->releaod_sprites[2].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[2].img.img, &state->releaod_sprites[2].img.bits_per_pixel, &state->releaod_sprites[2].img.line_length, &state->releaod_sprites[2].img.endian);
    state->releaod_sprites[3].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr11.xpm", &state->releaod_sprites[3].width, &state->releaod_sprites[3].height);
    state->releaod_sprites[3].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[3].img.img, &state->releaod_sprites[3].img.bits_per_pixel, &state->releaod_sprites[3].img.line_length, &state->releaod_sprites[3].img.endian);
    state->releaod_sprites[4].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr12.xpm", &state->releaod_sprites[4].width, &state->releaod_sprites[4].height);
    state->releaod_sprites[4].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[4].img.img, &state->releaod_sprites[4].img.bits_per_pixel, &state->releaod_sprites[4].img.line_length, &state->releaod_sprites[4].img.endian);
    state->releaod_sprites[5].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr13.xpm", &state->releaod_sprites[5].width, &state->releaod_sprites[5].height);
    state->releaod_sprites[5].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[5].img.img, &state->releaod_sprites[5].img.bits_per_pixel, &state->releaod_sprites[5].img.line_length, &state->releaod_sprites[5].img.endian);
    state->releaod_sprites[6].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr14.xpm", &state->releaod_sprites[6].width, &state->releaod_sprites[6].height);
    state->releaod_sprites[6].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[6].img.img, &state->releaod_sprites[6].img.bits_per_pixel, &state->releaod_sprites[6].img.line_length, &state->releaod_sprites[6].img.endian);
    state->releaod_sprites[7].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr15.xpm", &state->releaod_sprites[7].width, &state->releaod_sprites[7].height);
    state->releaod_sprites[7].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[7].img.img, &state->releaod_sprites[7].img.bits_per_pixel, &state->releaod_sprites[7].img.line_length, &state->releaod_sprites[7].img.endian);
    state->releaod_sprites[8].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr16.xpm", &state->releaod_sprites[8].width, &state->releaod_sprites[8].height);
    state->releaod_sprites[8].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[8].img.img, &state->releaod_sprites[8].img.bits_per_pixel, &state->releaod_sprites[8].img.line_length, &state->releaod_sprites[8].img.endian);
    state->releaod_sprites[9].img.img = mlx_xpm_file_to_image (state->vars->mlx, "frames/fr17.xpm", &state->releaod_sprites[9].width, &state->releaod_sprites[9].height);
    state->releaod_sprites[9].img.addr = (int *)mlx_get_data_addr (state->releaod_sprites[9].img.img, &state->releaod_sprites[9].img.bits_per_pixel, &state->releaod_sprites[9].img.line_length, &state->releaod_sprites[9].img.endian);
}