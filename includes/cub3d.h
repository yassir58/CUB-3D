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
#define TILE_SIZE 32
#define ROT_ANGLE (M_PI / 2) // 90 deg
#define moveSpeed 3.0
#define rotationSpeed (3 * (M_PI / 180))
# define XK_ESCAPE  53
# define XK_LEFT    123
# define XK_UP     126
# define XK_RIGHT  124
# define XK_DOWN   125
# define KEY_PRESS 2
# define DESTROY_NOTIFY 17
# define BUTTON_PRESS 4

typedef struct s_map_list 
{
    char *column;
    struct s_map_list *next;
} t_map_list ;


typedef struct s_game_data
{
    int tile_size;
    int row_number;
    int col_number;
    double **cos_sin_table;
} t_game_data;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;


typedef struct s_grid_data 
{
    int col;
    int row;
    int rect_width;
    int rect_height;
    int space_color;
    int wall_color;
} t_grid_data;

typedef struct s_player 
{
    int x;
    int y;
    int radius;
    int turnDirection;
    int walkDirection;
} t_player;


typedef struct s_vars 
{
    void *mlx;
    void *mlx_win;
} t_vars;

t_map_list *create_map_list (char *map);
void push_to_list (t_map_list **map, char *column);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void draw_rect (t_img *data, int x, int y, int width, int height, int color);
void calculate_grid (t_map_list *list, int *rect_width, int *rect_height, int *col, int *row);
void draw_grid (t_map_list *list, t_grid_data grid, t_img *img);
void draw_row (t_map_list *tmp, t_grid_data grid, t_img *img, int *j, int *x, int y);
void draw_player (t_img *data, int x, int y,double radius,  int color);
int	handle_keypress(int keycode, t_vars *vars);
#endif 