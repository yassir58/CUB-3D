#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include "../src/lib/libft/libft.h"
#include "../src/lib/gnl/get_next_line.h"
#include <mlx.h>


// Variables related to the ray caster.
#define FOV 60
#define FEILD_OF_VIEW_ANGLE ((FOV * (M_PI / 180)))
#define TILE_SIZE 32
#define RAY_THICKNESS 5

#define RES_X 1080
#define RES_Y 820
#define SPACE_CLR 0x00FFFFFF
#define WALL_CLR  0x002A0944
#define ROT_ANGLE (M_PI / 2) // 90 deg
#define moveSpeed 4
#define rotationSpeed 4
# define XK_ESCAPE  53
# define XK_LEFT    0
# define XK_UP      13
# define XK_RIGHT   2
# define XK_DOWN    1
# define KEY_PRESS  2
# define DESTROY_NOTIFY 17
# define BUTTON_PRESS 4
# define WALL 0
# define EMPTY_SPACE 1
# define PLAYER     2
# define RIGHT      0
# define LEFT       1
# define DOWN       2
# define UP         3
# define R_LEFT     123
# define R_UP       126
# define R_RIGHT    124
# define R_DOWN     125
# define N 270
# define S 90
# define W 180
# define E 360

# define RAY_UP 1
# define RAY_DOWN 2
# define RAY_LEFT 3
# define RAY_RIGHT 4

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
    int index;
    struct s_game_params *next;
} t_game_params;

typedef struct s_game_data
{
    int tile_size;
    int row_number;
    int col_number;
    int window_height;
    int window_width;
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


typedef struct s_intersection_data {
    double xstep;
    double ystep;
    double xintercept;
    double yintercept;
    double wallHitX;
    double wallHitY;
    double wallHorzHitX;
    double wallHorzHitY;
    double wallVertHitX;
    double wallVertHitY;
    double nextHorzTouchX;
    double nextHorzTouchY;
    double nextVertTouchX;
    double nextVertTouchY;
    double distanceHorizontal;
    double distanceVertical;
    bool wallHorzIntesected;
    bool wallVertIntesected;
} t_intersection_data;

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
    double turnDirection;
    double walkDirection;
    int d_x;
    int d_y;
    int d_length;
    int v_angle;
} t_player;

typedef struct s_vars 
{
    void *mlx;
    void *mlx_win;
} t_vars;

typedef struct s_global_state
{
    t_vars *vars;
    t_game_data *data;
    t_grid_data *grid;
    t_player *player;
    t_img img;
} t_global_state;

t_global_state g_data;

/**
 * @brief Init the simulation data
 * 
 * @param void
 * @return t_global_state* 
 */
t_global_state *init_simulation_data(void);

t_map_list *create_map_list (char *map);
void    push_to_list(t_map_list **map, char *column);
void    my_mlx_pixel_put(t_img *data, int x, int y, int color);
void    draw_rect (int x, int y, int color, t_global_state *state);
void    calculate_grid(t_map_list *list, int *col, int *row);
void    draw_grid (t_global_state *state);
void    draw_row (int i, int *j, int *x, int y, t_global_state *state);
void    parse_map(char *path, t_game_data *data);
void    init_window (t_map_list *map, t_global_state *state);
char    **get_map_vector (t_map_list *list, t_global_state *state);
void    move_player (int flag, t_global_state *state);
void    init_player (t_global_state *state);
int     check_outside_map (int flag);
int     position_in_map (int x);
int     check_for_wall (int x, int y, t_global_state *state);
void    draw_line (int x, int y, t_global_state *state);
void    draw_player (int color, t_global_state *state);
int     handle_keypress(int keycode, t_global_state *state);
void    get_rotation_cords (int *x_2, int *y_2, double angle, t_global_state *state);
double  deg_to_radian (int deg);
void    DDA(int X0, int Y0, int X1, int Y1, t_global_state *state);
void    rerender_map (t_global_state *state);
void    rotate_player (int direction, t_global_state *state);


// Parse list related functions
t_game_params	*new_params(char *key, char *value, int index);
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
// Map validation

void    validate_map(char **map, int map_size);

// Error management

void    app_error(int code);

#endif 