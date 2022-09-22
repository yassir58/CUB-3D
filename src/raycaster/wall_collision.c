
#include "../../includes/cub3d.h"


int checkCoordinatesWall(double x, double y, t_global_state *state)
{
    double X;
    double Y;

    X = floor(x / state->data->tileX);
    Y = floor(y / state->data->tileY);
    if (!(X < state->grid->col && Y < state->grid->row))
        return (1);
    if (state->data->map[(int)Y][(int)X] == '1')
            return (1);
    return (0);
}

int checkCoordinatesWallTest(double x, double y, t_global_state *state, int flag)
{
    double X;
    double Y;
    int moveSpeed;

    moveSpeed = state->player->moveSpeed;
    X = floor(x / state->data->tileX);
    Y = floor(y / state->data->tileY);
    if (flag == UP && state->cast->distance_to_wall - moveSpeed  < 2)
            return (1);
    else if (flag == DOWN && state->cast->distance_to_wall + moveSpeed < 2)
            return (1);
    if (!(X > 0 && X < state->grid->col && Y > 0 && Y < state->grid->row))
        return (1);
    if (state->data->map[(int)Y][(int)X] == '1')
            return (1);
    return (0);
}
