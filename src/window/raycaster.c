#include "../../includes/cub3d.h"


int get_angle_direction(double rayAngle)
{
    bool rayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
    bool rayFacingRight = (rayAngle < (M_PI_2) || rayAngle > (1.5 * M_PI));
    if (rayFacingDown)
        return (RAY_DOWN);
    else if (!rayFacingDown)
        return (RAY_UP);
    else if (rayFacingRight)
        return (RAY_RIGHT);
    else if (!rayFacingRight)
        return (RAY_LEFT);
}

int checkCoordinatesWall(double x, double y, t_game_data *data)
{
    char **map;
    int X;
    int Y;

    //! Here i should return 1 if x or y is out of boundes
    X = floor(x / TILE_SIZE);
    Y = floor(y / TILE_SIZE);
    map = convert_lines_table(data->lines);
    if (map[X][Y] == '1')
        return (1);
    return (0);
}

double calculateDistance(double x, double y, double x1, double y1)
{
    double distance;

    distance = sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y)));
    return (distance);
}

double getCorrectAgnle(double angle)
{
    double normalizedAngle;

    normalizedAngle = 0;
    normalizedAngle = fmod(angle, (M_PI * 2));
    if (angle < 0)
        normalizedAngle = angle + (M_PI * 2);
    return (normalizedAngle);
}

void    castRay(double rayAngle, t_intersection_data *data, t_global_state *state)
{
    double horizontalDistance;
    double verticalDistance;
    double rayDistance;

    getHorzIntersection(rayAngle, data, state);
    getVertIntersection(rayAngle, data, state);
    if (data->wallHorzIntesected)
        horizontalDistance = calculateDistance(state->player->initx, state->player->inity, data->wallHorzHitX, data->wallHorzHitY);
    if (data->wallVertIntesected)
        verticalDistance = calculateDistance(state->player->initx, state->player->inity, data->wallVertHitX, data->wallVertHitY);
    if (verticalDistance > horizontalDistance)
    {
        rayDistance = verticalDistance;
        data->wallHitX = data->wallHorzHitX;
        data->wallHitY = data->wallHorzHitY;
    }
    else
    {
        rayDistance = horizontalDistance;
        data->wallHitX = data->wallVertHitX;
        data->wallHitY = data->wallVertHitY;
    }
    //TODO: Draw a line in the canvas using the wallHitX and wallHitY
    // Here will be the code that will be responsible for casting one ray.
}

void    getHorzIntersection(double rayAngle, t_intersection_data *data, t_global_state *state)
{
    data->wallHorzIntesected = false;
    data->yintercept = floor(state->player->inity / TILE_SIZE) * TILE_SIZE;
    if (get_angle_direction(rayAngle) == RAY_DOWN)
        data->yintercept += TILE_SIZE;
    data->xintercept = state->player->initx + ((data->yintercept - state->player->inity) / tan(rayAngle));
    data->ystep = TILE_SIZE;
    if (get_angle_direction(rayAngle) == RAY_UP)
        data->ystep *= -1;
    data->xstep = data->ystep / tan(rayAngle);
    if (get_angle_direction(rayAngle) == RAY_LEFT && data->xstep > 0)
        data->xstep *= -1;
    if (get_angle_direction(rayAngle) == RAY_RIGHT && data->xstep < 0)
        data->xstep *= -1;
    data->nextHorzTouchX = data->xintercept;
    data->nextHorzTouchY = data->yintercept;
    if (get_angle_direction(rayAngle) == RAY_UP)
        data->nextHorzTouchY -= 1;
    while (data->nextHorzTouchX >= 0 && data->nextHorzTouchX <= state->data->window_width && data->nextHorzTouchY >= 0 && data->nextHorzTouchY <= state->data->window_height)
    {
        if (checkCoordinatesWall(data->nextHorzTouchX, data->nextHorzTouchY, state->data))
        {
            data->wallHorzIntesected = true;
            data->wallHorzHitX = data->nextHorzTouchX;
            data->wallHorzHitY = data->nextHorzTouchY;
            break;
        }
        else
        {
            data->nextHorzTouchX += data->xstep;
            data->nextVertTouchY += data->ystep;
        }
    }
}

void    getVertIntersection(double rayAngle, t_intersection_data *data, t_global_state *state)
{
    data->wallVertIntesected = false;
    data->xintercept = floor(state->player->initx / TILE_SIZE) * TILE_SIZE;
    if (get_angle_direction(rayAngle) == RAY_RIGHT)
        data->xintercept += TILE_SIZE;
    data->yintercept = state->player->inity + ((data->xintercept - state->player->initx) * tan(rayAngle));
    data->xstep = TILE_SIZE;
    if (get_angle_direction(rayAngle) == RAY_LEFT)
        data->xstep *= -1;
    data->ystep = data->xstep * tan(rayAngle);
    if (get_angle_direction(rayAngle) == RAY_UP && data->ystep > 0)
        data->xstep *= -1;
    if (get_angle_direction(rayAngle) == RAY_DOWN && data->ystep < 0)
        data->xstep *= -1;
    data->nextVertTouchX = data->xintercept;
    data->nextVertTouchY = data->yintercept;
    if (get_angle_direction(rayAngle) == RAY_LEFT)
        data->nextVertTouchX -= 1;
    while (data->nextVertTouchX >= 0 && data->nextVertTouchX <= state->data->window_width && data->nextVertTouchY >= 0 && data->nextVertTouchY <= state->data->window_height)
    {
        if (checkCoordinatesWall(data->nextVertTouchX, data->nextVertTouchY, state->data))
        {
            data->wallVertIntesected = true;
            data->wallVertHitX = data->nextVertTouchX;
            data->wallVertHitY = data->nextVertTouchY;
            break;
        }
        else
        {
            data->nextVertTouchX += data->xstep;
            data->nextVertTouchY += data->ystep;
        }
    }
}

void    raycaster(t_game_data *game, t_global_state *state)
{
    int columnId;
    int raysNumber;
    double rayAngle;
    t_intersection_data *data;

    columnId = 0;
    raysNumber = state->data->window_width / RAY_THICKNESS;
    rayAngle = state->player->v_angle - (FEILD_OF_VIEW_ANGLE / 2);

    data = (t_intersection_data *)malloc(sizeof(t_intersection_data));
    if (!data)
        return ;

}


//TODO: Create Cast ray function that will cast only one ray based on 
//?DONE: Create a function that will calculate the distance between two dots
//?DONE: Create a function that will round the angle
//?DONE: Caluculate horizontal interections: getHorzIntersection
//?DONE: Caluculate vertical interections: getVertIntersection
//?DONE: Get where the ray is facing
//?DONE: Create a function that will check that the current x and y position are a wall or not