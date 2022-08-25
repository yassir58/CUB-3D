#include "../includes/cub3d.h"


void calculate_grid (t_map_list *list, int *col, int *row)
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
}


void draw_grid (void)
{
    int x, y ,i ,j;

    x = 0, y = 0, i = 0, j = 0;
   
    while (i < g_data.grid.row)
    {
        draw_row (i, &j , &x, y);
        j = 0;
        x = 0;
        y += TILE_SIZE;
        i++;
    }
}


void draw_row (int i, int *j, int *x, int y)
{
    while (*j < g_data.grid.col)
    {  
        if (g_data.data.map[i][*j] == '1')
            draw_rect (*x, y,WALL_CLR);
        else if (g_data.data.map[i][*j] == 'P')
        {
            draw_rect (*x, y, SPACE_CLR);
            if (g_data.player.initx == 0 && g_data.player.inity == 0)
            {
                g_data.player.initx = *x + (TILE_SIZE / 2);
                g_data.player.inity = y + (TILE_SIZE / 2);
            }
            draw_player (0x00FF0000);
        }
        else
            draw_rect (*x, y, SPACE_CLR);
        *x += TILE_SIZE;
        (*j)++;
    }
    
}


void draw_line (int x, int y)
{
    int x_2, y_2;
    double angle;

    x_2 = x;
    y_2 = y;
    angle = deg_to_radian (W);
    get_rotation_cords (&x_2, &y_2, angle);
    DDA (x , y , x_2, y_2);
    printf ("|x2= %d|y2 = %d|\n", x_2, y_2);
}



void DDA(int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put (&g_data.img, X, Y, 0x00FBDF07); // put pixel at (X,Y)
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step
        // delay(100);          // for visualization of line-
                             // generation step by step
    }
}


void get_rotation_cords (int *x_2, int *y_2, double angle)
{
    *x_2 = *x_2 + (cos (angle)  *  g_data.player.d_length);
    *y_2 = *y_2 + (sin (angle)  *  g_data.player.d_length);
}