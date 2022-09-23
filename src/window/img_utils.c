#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_global_state *state, int x, int y, int color, t_img *img)
{
	t_img *data;

	if (img == NULL)
		data = &state->img;
	else
		data = img;
	if ((x >= 0 && x < state->data->window_width) && (y >= 0 && y < state->data->window_height))
		data->addr[(state->data->window_width * y) + x] = color;
}
void draw_minirect (int x, int y, int color, t_global_state *state)
{
	int i;
	int j;
	int clr;

	i = 0;
	j = 0;
	clr = 0;
	while (i <= MINIMAP_CEL)
	{
		while (j <= MINIMAP_CEL)
		{
			clr = color;
			my_mlx_pixel_put (state , (x + j), (y + i), clr, NULL);
			j++;
		}
		j = 0;
		i++;
	}
}

void draw_rect (int x, int y, int color, t_global_state *state)
{
	int i;
	int j;
	int clr;

	i = 0;
	j = 0;
	clr = 0;
	while (i <= state->data->tileY)
	{
		while (j <= state->data->tileX)
		{
			if (i == 0 || j == 0 || (j == state->data->tileX) || (i == state->data->tileY))
				clr = 0x008ACB88;
			else
			clr = color;
			my_mlx_pixel_put (state , (x + j), (y + i), clr, &testing_img);
			j++;
		}
		j = 0;
		i++;
	}
}

void draw_column (int x, int y, t_global_state *state, double colHeight)
{
	int start;
	int end;
	int texelClr;
	int txtOffsetY;

	start = y;
	end = colHeight;
	while (end--)
	{
		txtOffsetY = (start - y) * (state->current.height / colHeight);
		texelClr = state->current.img.addr[(state->current.width * txtOffsetY) + state->cast->txtOffsetX];
		my_mlx_pixel_put (state , x, start, texelClr, NULL);
		start++;
	}
}

int handle_events_2  (t_global_state *state)
{
     if (state->move_up)
        move_player_2 (UP, state);
    if (state->move_down)
        move_player_2  (DOWN, state);
    if (state->move_left)
        move_player_2 (LEFT, state);
    if (state->move_right)
        move_player_2 (RIGHT, state);
    if (state->rotate_left)
        move_player_2  (L, state);
    if (state->rotate_right)
        move_player_2 (R, state);
    handle_shoot_sprite (state);
    return (0);   
}