#include "../includes/cub3d.h"

int mouse_handle(int x, int y, void *param)
{
    t_global_state *state;
    int prevPos;
    int calculatedPos;

    (void)y;
    state = (t_global_state *)param;
    if (x > 0 && x <= RES_X && y > 0 && y <= RES_Y)
    {
         prevPos = state->data->prev_pos_mouse;
        calculatedPos = x - prevPos;
        if (calculatedPos < 0)
            state->player->v_angle -= 2;
        else
            state->player->v_angle += 2;
        state->data->prev_pos_mouse = x;
        rerender_map(state);
    }
    return (0);
}