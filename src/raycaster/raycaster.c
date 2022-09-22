#include "../../includes/cub3d.h"

double calculateDistance(double x, double y, double x1, double y1)
{
    double distance;

    distance = sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y)));
    return (distance);
}

void    calculate_ray_distance(t_global_state *state, t_raycast *data)
{
    if (data->wallHorzIntesected)
        data->horizontalDistance = calculateDistance(state->player->initx, state->player->inity, \
        data->wallHorzHitX, data->wallHorzHitY);
    else
        data->horizontalDistance = INT_MAX;
    if (data->wall_vert_intesected)
        data->verticalDistance = calculateDistance(state->player->initx, state->player->inity, \
        data->wallVertHitX, data->wallVertHitY);
    else
        data->verticalDistance = INT_MAX;
}

void    renderTextures(t_global_state *state, t_raycast *data, double ray_angle)
{
    if (data->wasIntersectionVertical)
    {
		if (ray_facing_left(ray_angle))
            state->current = state->west_texture;
		else
			state->current = state->east_texture;
        data->coff = data->wallHitY / state->data->tileX - \
        (int)(data->wallHitY / state->data->tileX);
        data->txtOffsetX = (int)(data->coff * state->current.width);
    }
    else
    {
		if (ray_facing_up(ray_angle))
        	state->current = state->north_texture;
		else
			state->current = state->south_texture;
        data->coff = data->wallHitX / state->data->tileX - \
        (int)(data->wallHitX / state->data->tileX);
        data->txtOffsetX = (int) (data->coff * state->current.height);
    }
}

double    cast_ray(double ray_angle, t_raycast *data, t_global_state *state)
{
    horz_ray(ray_angle, data, state);
    vert_ray(ray_angle, data, state);
    calculate_ray_distance(state, data);
    if (data->verticalDistance > data->horizontalDistance)
    {
        data->wasIntersectionVertical = false;
        data->rayDistance = data->horizontalDistance;
        data->wallHitX = data->wallHorzHitX;
        data->wallHitY = data->wallHorzHitY;
    }
    else
    {
        data->wasIntersectionVertical = true;
        data->rayDistance = data->verticalDistance;
        data->wallHitX = data->wallVertHitX;
        data->wallHitY = data->wallVertHitY;
    }
    renderTextures(state, data, ray_angle);
    return (data->rayDistance * cos(deg_to_radian(state->player->v_angle) - ray_angle));
}


void    HorzIntercect(double ray_angle, t_raycast *data, t_global_state *state)
{
    int tileY;
    
    tileY = state->data->tileY;
    data->wallHorzIntesected = false;
    data->yintercept = floor(state->player->inity / tileY) * tileY;
    if (ray_facing_down(ray_angle))
        data->yintercept += tileY;
    data->xintercept = state->player->initx + ((data->yintercept - state->player->inity) / tan(ray_angle));
    
    data->ystep = tileY;
    if (!ray_facing_down(ray_angle))
        data->ystep *= -1;

    data->xstep = data->ystep / tan(ray_angle);
    if (ray_facing_left(ray_angle) && data->xstep > 0)
        data->xstep *= -1;
    if (ray_facing_right(ray_angle) && data->xstep < 0)
        data->xstep *= -1;
}

void   horz_ray(double ray_angle, t_raycast *data, t_global_state *state)
{
    HorzIntercect(ray_angle, data, state);
    data->nextHorzTouchX = data->xintercept;
    data->nextHorzTouchY = data->yintercept;
    if (ray_facing_up(ray_angle))
        data->nextHorzTouchY -= 1;
    while (data->nextHorzTouchX >= 0 && data->nextHorzTouchX <= state->data->window_width \
    && data->nextHorzTouchY >= 0 && data->nextHorzTouchY <= state->data->window_height)
    {
        if (checkCoordinatesWall(data->nextHorzTouchX, data->nextHorzTouchY, state))
        {
            data->wallHorzIntesected = true;
            if (ray_facing_up(ray_angle))
                data->nextHorzTouchY += 1;
            data->wallHorzHitX = data->nextHorzTouchX;
            data->wallHorzHitY = data->nextHorzTouchY;
            break;
        }
        else
        {
            data->nextHorzTouchX += data->xstep;
            data->nextHorzTouchY += data->ystep;
        }
    }
}

void    vertIntercet(double ray_angle, t_raycast *data, t_global_state *state)
{
    int tileX;
    
    tileX = state->data->tileX;
    data->wall_vert_intesected = false;
    data->xintercept = floor(state->player->initx / tileX) * tileX;
    if (ray_facing_right(ray_angle))
        data->xintercept += tileX;
    data->yintercept = state->player->inity + ((data->xintercept - state->player->initx) * tan(ray_angle));
    
    data->xstep = tileX;
    if (ray_facing_left(ray_angle))
        data->xstep *= -1;

    data->ystep = data->xstep * tan(ray_angle);
    if (ray_facing_up(ray_angle) && data->ystep > 0)
        data->ystep *= -1;
    if (ray_facing_down(ray_angle) && data->ystep < 0)
        data->ystep *= -1;
}

void    vert_ray(double ray_angle, t_raycast *data, t_global_state *state)
{
    vertIntercet(ray_angle, data, state);
    data->next_vert_touchx = data->xintercept;
    data->next_vert_touchy = data->yintercept;
    if (ray_facing_left(ray_angle))
        data->next_vert_touchx -= 1;
    while (data->next_vert_touchx >= 0 && data->next_vert_touchx <= RES_X \
    && data->next_vert_touchy >= 0 && data->next_vert_touchy <= RES_Y)
    {
        if (checkCoordinatesWall(data->next_vert_touchx, data->next_vert_touchy, state))
        {
            data->wall_vert_intesected = true;
            if (ray_facing_left(ray_angle))
                data->next_vert_touchx += 1;
            data->wallVertHitX = data->next_vert_touchx;
            data->wallVertHitY = data->next_vert_touchy;
            break;
        }
        else
        {
            data->next_vert_touchx += data->xstep;
            data->next_vert_touchy += data->ystep;
        }
    }
}

void    raycaster(t_global_state *state)
{
    int column_id;
    double ray_angle;
    double ray_distance;
    double col_height;
   
    column_id = 0;
    col_height = 0;
    ray_distance = 0;
    ray_angle = deg_to_radian(state->player->v_angle) - (FOV_ANGLE / 2.0);
    state->cast->pp_distance = (RES_X_2)  / (tan(FOV_ANGLE / 2.0));
    color(state, state->data->floor, RES_Y_2);
    color(state, state->data->ceil, 0);
    while (column_id < RES_X)
    {
        ray_distance =  cast_ray(get_correct_angle(ray_angle), state->cast, state);
        if (column_id == RES_X_2)
            state->cast->distance_to_wall = ray_distance;
        col_height = (state->data->tileY / ray_distance) * state->cast->pp_distance;
        draw_column (column_id, ((RES_Y_2) - (col_height / 2)), state, col_height);
        ray_angle += FOV_ANGLE / RES_X;
        column_id += 1;
    }
    draw_minimap (state);
}
