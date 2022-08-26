#include "../includes/cub3d.h"


void init_window (t_map_list *map)
{
    g_data.vars.mlx = mlx_init ();
    calculate_grid (map, &(g_data.grid.col), &(g_data.grid.row));
    init_player ();
    g_data.data.height = (g_data.grid.row * 32);
    g_data.data.width = (g_data.grid.col * 32);
    g_data.vars.mlx_win = mlx_new_window (g_data.vars.mlx, (g_data.grid.col * TILE_SIZE), (g_data.grid.row * TILE_SIZE), "CUB3D");
    g_data.img.img = mlx_new_image (g_data.vars.mlx, g_data.data.width, g_data.data.width);
    g_data.img.addr = mlx_get_data_addr (g_data.img.img, &(g_data.img.bits_per_pixel), &(g_data.img.line_length), &(g_data.img.endian));
    g_data.data.map = get_map_vector (map);
}

char **get_map_vector (t_map_list *list)
{
    char **map_vector;
    t_map_list *tmp;
    t_map_list *ptr;
    int i;

    i = 0;
    tmp = list;
    map_vector = malloc (sizeof (char *) * (g_data.grid.row + 1));
    if (!map_vector)
        return (NULL);
    while (tmp)
    {
        ptr = tmp;
        map_vector[i] = ft_strdup (tmp->column);
        tmp = tmp->next;
        free (tmp);
        i++;
    }
    map_vector[i] = NULL;
    return (map_vector);
}


void init_player (void)
{
    g_data.player.initx = 0;
    g_data.player.inity = 0;
    g_data.player.radius = 2;
    g_data.player.turnDirection = 0;
    g_data.player.walkDirection = 0;
    g_data.player.x_cord = 0;
    g_data.player.y_cord = 0;
    g_data.player.d_x = 0;
    g_data.player.d_y = 0;
    g_data.player.d_length = 20;
    g_data.player.v_angle = W;
}