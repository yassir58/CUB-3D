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
    int **cos_sin_table;
} t_game_data;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;


t_map_list *create_map_list (char *map);
void push_to_list (t_map_list **map, char *column);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);


#endif 