#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include "../src/lib/libft/libft.h"
#include "../src/lib/gnl/get_next_line.h"
#include <mlx.h>

#define FEILD_OF_VIEW_ANGLE ((FOV * (M_PI / 180)))
#define FOV 60
#define RES_X 1080
#define RES_Y 820

#define WALL_CHARS "01NSWE"

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_map_list 
{
    char *column;
    struct s_map_list *next;
} t_map_list;

typedef struct s_game_params 
{
    char *key;
    char *value;
    struct s_game_params *next;
} t_game_params;

typedef struct s_game_data
{
    int height;
    int width;
    int floor;
    int ceil;
    int **map;
    t_game_params *params;
} t_game_data;

typedef struct s_grid_data 
{
    int col;
    int row;
    int rect_width;
    int rect_height;
    int space_color;
    int wall_color;
} t_grid_data;


t_map_list *create_map_list (char *map);
void push_to_list (t_map_list **map, char *column);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void draw_rect (t_img *data, int x, int y, int width, int height, int color);
void calculate_grid (t_map_list *list, int *rect_width, int *rect_height, int *col, int *row);
void draw_grid (t_map_list *list, t_grid_data grid, t_img *img);
void draw_row (t_map_list *tmp, t_grid_data grid, t_img *img, int *j, int *x, int y);
void    parse_map(char *path, t_game_data *data);


// Parse list related functions

t_game_params   *new_params(char *key, char *value);
void            add_param(t_game_params **lst, t_game_params *new);
int             search_params_list(char *key, t_game_params *list);
void            print_params_list(t_game_params *list);

#endif 