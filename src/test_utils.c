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


void draw_grid (t_global_state *state)
{
    int x, y ,i ,j;

    x = 0, y = 0, i = 0, j = 0;
   
    while (i < state->grid->row)
    {
        draw_row (i, &j , &x, y, state);
        j = 0;
        x = 0;
        y += state->data->tileY;
        i++;
    }
}


void draw_row (int i, int *j, int *x, int y, t_global_state *state)
{
    while (*j < state->grid->col)
    {  
        if (state->data->map[i][*j] == '1')
            draw_rect (*x, y,0x00FF0155, state);
        else if (state->data->map[i][*j] == 'P')
        {
            draw_rect (*x, y, SPACE_CLR, state);
            if (state->player->initx == 0 && state->player->inity == 0)
            {
                state->player->initx = *x + (state->data->tileX / 2);
                state->player->inity = y + (state->data->tileY / 2);
            }
            draw_player (0x00FF0000, state);
        }
        else if (state->data->map[i][*j] == '0')
            draw_rect (*x, y, SPACE_CLR, state);
        *x += state->data->tileX;
        (*j)++;
    }
    
}


void draw_line (int x, int y, t_global_state *state)
{
    int x_2, y_2;
    double angle;

    x_2 = x;
    y_2 = y;
    angle = deg_to_radian (state->player->v_angle);
    get_rotation_cords (&x_2, &y_2, angle, state);
    DDA (x , y , x_2, y_2, state);
    // printf ("|x2= %d|y2 = %d|\n", x_2, y_2);
}



void DDA(int X0, int Y0, int X1, int Y1, t_global_state *state)
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
        my_mlx_pixel_put (state, X, Y, 0x00FBDF07, NULL); // put pixel at (X,Y)
        X += Xinc;           // increment in x at each step
        Y += Yinc;           // increment in y at each step
        // delay(100);          // for visualization of line-
                             // generation step by step
    }
}


void get_rotation_cords (int *x_2, int *y_2, double angle, t_global_state *state)
{
    *x_2 = *x_2 + (cos (angle)  *  state->player->d_length);
    *y_2 = *y_2 + (sin (angle)  *  state->player->d_length);
}


void init_image (t_global_state *state)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < (state->data->window_height))
    {
        while (j < (state->data->window_width))
        {
            my_mlx_pixel_put (state, j, i, 0x00000000, &testing_img);
            j++;
        }
        j = 0;
        i++;
    }
}



void color (t_global_state *state, int color, int start)
{
    int i;
    int j;
    int max;

    i = start;
    j = 0;
    max = state->data->window_height;
    if (start == 0)
        max = state->data->window_height / 2;
    while (i < max)
    {
        while (j < state->data->window_width)
        {
            my_mlx_pixel_put (state, j, i, color, &testing_img);
            j++;
        }
        j = 0;
        i++;
    }
}