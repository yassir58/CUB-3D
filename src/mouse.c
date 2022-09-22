#include "../includes/cub3d.h"

int mouse_handle(int x, int y, void *param)
{
    t_global_state *state;
    int prevPos;
    int calculatedPos;

    (void)y;
    state = (t_global_state *)param;
    prevPos = state->data->prev_pos_mouse;
    calculatedPos = x - prevPos;
    if (calculatedPos < 0)
        state->player->v_angle -= 2;
    else
        state->player->v_angle += 2;
    rerender_map(state);
    state->data->prev_pos_mouse = x;
    return (0);
}
