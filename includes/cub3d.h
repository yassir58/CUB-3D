#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include "../src/lib/libft/libft.h"
#include "../src/lib/gnl/get_next_line.h"
#include <mlx.h>


//// testing 

// Variables related to the ray caster.
#define FOV 60
#define FEILD_OF_VIEW_ANGLE ((FOV * (M_PI / 180)))
#define RAY_THICKNESS 1

#define MINIMAP_CEL 5
#define MINIMAP_ROW 40
#define MINIMAP_RES 200
#define RES_X 1000
#define RES_Y 800
#define SPACE_CLR 0x00FFFFFF
// #define WALL_CLR  0x002A0944
#define WALL_CLR  0x00000000
#define ROT_ANGLE (M_PI / 2) // 90 deg
#define rotationSpeed 4

// MAC keycodes
# define XK_ESCAPE  53
# define LeaveNotify 17
# define XK_LEFT    0
# define XK_UP      13
# define XK_RIGHT   2
# define XK_DOWN    1
# define R_LEFT     123
# define R_UP       126
# define R_RIGHT    124
# define R_DOWN     125
# define SHOOT 15

# define ROWS 14
# define COLS 37

// Linux keycodes
// # define XK_ESCAPE  65307
// # define XK_LEFT    97
// # define XK_UP      119
// # define XK_RIGHT   100
// # define XK_DOWN    115
// # define R_LEFT     65361
// # define R_UP       65362
// # define R_RIGHT    65363
// # define R_DOWN     65364

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
# define L 303
# define R 302
# define N 270
# define S 90
# define W 180
# define E 360

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
    int tsize;
    int row_number;
    int col_number;
    int window_height;
    int window_width;
    int tileX;
    int tileY;
    int floor;
    int ceil;
    int prev_pos_mouse;
    char playerDirection;
    char **map;
    t_map_line *lines;
    t_game_params *params;
} t_game_data;

typedef struct	s_img {
	void	*img;
	int	*addr;
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
    bool wasIntersectionVertical;
    double projectPlaneDistance;
    double horizontalDistance;
    double verticalDistance;
    double coff;
    double rayDistance;
    int txtOffsetX;
    int distanceToWall;
} t_intersection_data;

typedef struct s_grid_data 
{
    int col;
    int row;
} t_grid_data;

typedef struct s_texture
{
    int     width;
    int     height;
    t_img img;
} t_texture;

typedef struct s_player 
{
    double initx;
    double inity;
    double minimap_x;
    double minimap_y;
    int x_cord;
    int y_cord;
    int radius;
    double turnDirection;
    double walkDirection;
    int d_x;
    int d_y;
    int d_length;
    int v_angle;
    int moveSpeed;
} t_player;

typedef struct s_vars 
{
    void *mlx;
    void *mlx_win;
} t_vars;

typedef struct s_sprites
{
    t_texture pistol1;
    t_texture pistol2;
    t_texture pistol3;
    t_texture pistol4;
    t_texture pistol5;
    t_texture shotgun1;
} t_sprites;

typedef struct s_global_state
{
    t_vars *vars;
    t_game_data *data;
    t_grid_data *grid;
    t_player *player;
    t_intersection_data *cast;
    t_img img;
    t_texture east_texture;
    t_texture north_texture;
    t_texture west_texture;
    t_texture south_texture;
    t_texture current;
    t_sprites *sprites;
    t_texture current_sprite;
} t_global_state;




t_global_state g_data;

/**
 * @brief Init the simulation data
 * 
 * @param void
 * @return t_global_state* 
 */

t_vars  testing_window;
t_img   testing_img;
double r_a;
t_global_state *init_simulation_data();
t_map_list *create_map_list (char *map);
void    push_to_list(t_map_list **map, char *column);
void	my_mlx_pixel_put(t_global_state *state, int x, int y, int color, t_img *img);
void    draw_rect (int x, int y, int color, t_global_state *state);
void calculate_grid (char **map, int *col, int *row);
void    draw_grid (t_global_state *state);
void    draw_row (int i, int *j, int *x, int y, t_global_state *state);
void    parse_map(char *path, t_global_state *state);
void    init_window (t_global_state *state);
char    **get_map_vector (t_map_list *list, t_global_state *state);
void    move_player (int flag, t_global_state *state);
void    init_player (t_global_state *state);
int     check_outside_map (int flag);
int     check_for_wall (int x, int y, t_global_state *state);
void    draw_line (int x, int y, t_global_state *state);
void    draw_player (int color, t_global_state *state);
int     handle_keypress(int keycode, t_global_state *state);
void    get_rotation_cords (int *x_2, int *y_2, double angle, t_global_state *state);
double  deg_to_radian (int deg);
int     radian_to_deg(double rad);
void    DDA(int X0, int Y0, int X1, int Y1, t_global_state *state);
void    rerender_map (t_global_state *state);
void    rotate_player (int direction, t_global_state *state);
void    init_image (t_global_state *state);
unsigned int get_pixel_color (int x, int y, t_img *img);
// Parse list related functions
t_game_params	*new_params(char *key, char *value);
t_map_line      *new_line(char *line);
int             search_params_list(char *key, t_game_params **list);
int             lines_number(t_map_line *list);
void            add_param(t_game_params **lst, t_game_params *new);
void            add_line(t_map_line **lst, t_map_line *new);
// Convert list to table
char            **convert_lines_table(t_map_line *list);
int             string_table_number(char **table);
// Reading file
char            *advanced_get_next_line(int fd, int status);
// Printing lists
void            print_lines_list(t_map_line *list);
void            print_params_list(t_game_params *list);
int	            game_param_size(t_game_params *lst);
// Map validation

char    **validate_map(char **map, int map_size, t_global_state *state);
// Extension validation
void    check_path(char *path);
void    validate_extension(char *path, char *ext);
int count_seperator(char *str, char c);
int get_color(char *str);
void    free_table(char **table);
int check_identifier(char *id);
int wall_line(char *line);
// Error management

void    app_error(int code);

// Ray casting related functions
void color (t_global_state *state, int color, int start);
void    getHorzIntersection(double rayAngle, t_intersection_data *data, t_global_state *state);
void    getVertIntersection(double rayAngle, t_intersection_data *data, t_global_state *state);
void    raycaster(t_global_state *state);
double    castRay(double rayAngle, t_intersection_data *data, t_global_state *state);
double  getCorrectAgnle(double angle);
double  calculateDistance(double x, double y, double x1, double y1);
int     checkCoordinatesWall(double x, double y, t_global_state *state);
int     get_angle_direction(double rayAngle);
double  getCorrectAngle(double angle);
void    draw_column (int x, int y, t_global_state *state, double colHeight);
int     mouse_handle(int x, int y, void *param);
char **get_key_value(char *str);
char *strip_whitespaces(char *str);
void init_player_position (t_global_state *state);
void minimap_position (t_global_state *state);
int  handle_leave (t_global_state *state);
void load_texture_images (t_global_state *state);
void init_game (t_global_state *state);
void draw_minimap (t_global_state *state);
int position_in_map (int cord, t_global_state *state);
void render_minimap_cel (int x, int y, t_global_state *state, int elm);
void draw_minimap_row (int player_x, int player_y,int y, t_global_state *state, int indx_x , int indx_y);
void draw_minimap_wall (int y, t_global_state *state, int indx_x);
void draw_minirect (int x, int y, int color, t_global_state *state);
int rayFacingDown(double rayAngle);
int rayFacingRight(double rayAngle);
int rayFacingUp(double rayAngle);
int rayFacingLeft(double rayAngle);
void init_sprites (t_global_state *state);
void handle_sprite (t_global_state *state);
void rerender_sprite (t_global_state *state, t_texture sprite);
int checkCoordinatesWallTest(double x, double y, t_global_state *state, int flag);
#endif 