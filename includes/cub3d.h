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
#define SPACE_CLR 0x00FFFFFF
#define WALL_CLR  0x002A0944
#define ROT_ANGLE (M_PI / 2) // 90 deg
#define moveSpeed 6
#define rotationSpeed (3 * (M_PI / 180))
# define XK_ESCAPE  53
# define XK_LEFT    123
# define XK_UP     126
# define XK_RIGHT  124
# define XK_DOWN   125
# define KEY_PRESS 2
# define DESTROY_NOTIFY 17
# define BUTTON_PRESS 4
# define WALL 0
# define EMPTY_SPACE 1
# define PLAYER 2
# define RIGHT 0
# define LEFT 1
# define DOWN 2
# define UP 3

#define WALL_CHARS "01NSWE "
#define WALL_LINE "1 "
#define PLAYER_CHARS "NSWE"

typedef struct s_map_line {
    char *line;
    struct s_map_line *next;
} t_map_line;

typedef struct s_game_params 
{
    char *key;
    char *value;
    struct s_game_params *next;
} t_game_params;

typedef struct s_game_data
{
    int tile_size;
    int row_number;
    int col_number;
    double **cos_sin_table;
    int height;
    int width;
    int floor;
    int ceil;
    char **map;
    t_map_line *lines;
    t_game_params *params;
} t_game_data;

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


typedef struct s_grid_data 
{
    int col;
    int row;
} t_grid_data;

typedef struct s_player 
{
    int initx;
    int inity;
    int x_cord;
    int y_cord;
    int radius;
    int turnDirection;
    int walkDirection;
} t_player;

typedef struct s_vars 
{
    void *mlx;
    void *mlx_win;
} t_vars;

typedef struct s_global_state
{
    t_vars vars;
    t_game_data data;
    t_grid_data grid;
    t_player player;
    t_img img;
} t_global_state;

t_global_state g_data;

t_map_list *create_map_list (char *map);
void    push_to_list(t_map_list **map, char *column);
void    my_mlx_pixel_put(t_img *data, int x, int y, int color);
void    draw_rect(int x, int y, int clr);
void    calculate_grid(t_map_list *list, int *col, int *row);
void    draw_grid(void);
void    draw_row(int i, int *j, int *x, int y);
void    parse_map(char *path, t_game_data *data);
void    init_window (t_map_list *map);
char    **get_map_vector (t_map_list *list);
void    move_player_right (void);
void    move_player_left (void);
void    move_player_down (void);
void    move_player_up (void);
void    init_player (void);
int     check_outside_map (int flag);
int     position_in_map (int x);
int     check_for_wall (int x, int y);
void draw_line (int start_x, int start_y, int end_x, int end_y);
void draw_player (int color);
int	handle_keypress(int keycode, t_vars *vars);

// Parse list related functions
t_game_params   *new_params(char *key, char *value);
t_map_line      *new_line(char *line);
int             search_params_list(char *key, t_game_params **list);
int             lines_number(t_map_line *list);
void            add_param(t_game_params **lst, t_game_params *new);
void            add_line(t_map_line **lst, t_map_line *new);
// Convert list to table
char            **convert_lines_table(t_map_line *list);
// Reading file
char            *advanced_get_next_line(int fd, int status);
// Printing lists
void            print_lines_list(t_map_line *list);
void            print_params_list(t_game_params *list);

#endif 