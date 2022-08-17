#include "../includes/cub3d.h"


void calculate_grid (t_map_list *list, int *rect_width, int *rect_height, int *col, int *row)
{
 
    t_map_list *temp;

    temp = list;
    *col = ft_strlen (temp->column) - 1;
    *row = 0;
    while (temp)
    {
        (*row)++;
        temp = temp->next;
    }
    *rect_height = 32;
    *rect_width = 32;
}


void draw_grid (t_map_list *list, t_grid_data grid, t_img *img)
{
    int x, y ,i ,j;
    int color;
    t_map_list *tmp;
  
    tmp = list;
    x = 0, y = 0, i = 0, j = 0, color = 0;
    printf ("|col %d| row %d| width %d| height %d|\n", grid.col, grid.row, grid.rect_width, grid.rect_height);
   
    while (i < grid.row)
    {
        draw_row (tmp, grid, img, &j , &x, y);
        j = 0;
        x = 0;
        y += grid.rect_height;
        printf ("[y:%d]\n", y);
        tmp = tmp->next;
        i++;
    }
}


void draw_row (t_map_list *tmp, t_grid_data grid, t_img *img, int *j, int *x, int y)
{
    printf ("x:%d y:%d\n", *x, y);
    while (*j < grid.col)
    {  
        if (tmp->column[*j] == '0')
            draw_rect (img, *x, y, grid.rect_width, grid.rect_height, grid.space_color);
        else if (tmp->column[*j] == '1')
            draw_rect (img, *x, y, grid.rect_width, grid.rect_height, grid.wall_color);
        else if (tmp->column[*j] == 'P')
        {
            draw_rect (img, *x, y, grid.rect_width, grid.rect_height, grid.space_color);
            draw_player (img, *x, y, 10, 0x00FF0000);
        }
        *x += grid.rect_width;
        (*j)++;
    }
    printf ("[x:%d]\n", *x);
}