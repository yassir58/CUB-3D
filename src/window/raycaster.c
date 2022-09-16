#include "../../includes/cub3d.h"


// int get_angle_direction(double rayAngle)
// {
//     bool rayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
//     bool rayFacingRight = (rayAngle > 0);
//     if (rayFacingDown)
//         return (RAY_DOWN);
//     else if (!rayFacingDown)
//         return (RAY_UP);
//     else if (rayFacingRight)
//         return (RAY_RIGHT);
//     else if (!rayFacingRight)
//         return (RAY_LEFT);
//     return (0);
// }

int rayFacingDown(double rayAngle)
{
    if (rayAngle > 0 && rayAngle < M_PI)
        return (1);
    return (0);
}

int rayFacingRight(double rayAngle)
{
    if (rayAngle < (M_PI_2) || rayAngle > (1.5 * M_PI))
        return (1);
    return (0);
}

int rayFacingUp(double rayAngle)
{
    if (!rayFacingDown(rayAngle))
        return (1);
    return (0);
}

int rayFacingLeft(double rayAngle)
{
    if (!rayFacingRight(rayAngle))
        return (1);
    return (0);
}

int checkCoordinatesWall(double x, double y, t_global_state *state)
{
    double X;
    double Y;
    // int i;

    // i = 0;

    //! Here i should return 1 if x or y is out of boundes
    // x += 1;
    // y += 1;
    X = floor(x / state->data->tileX);
    Y = floor(y / state->data->tileY);
    // map = convert_lines_table(data->lines);
    // printf("Before the segfault in convert function.\n");
    // while (i < string_table_number(data->map))
    // {
    //     printf("%s", data->map[i]);
    //     i++;
    // }
    // while (1);
    // printf("%c\n", data->map[Y][])
    if (!(X < state->grid->col && Y < state->grid->row))
        return (1);
    if (state->data->map[(int)Y][(int)X] == '1')
            return (1);
    return (0);
}

double calculateDistance(double x, double y, double x1, double y1)
{
    double distance;

    distance = sqrt(((x1 - x) * (x1 - x)) + ((y1 - y) * (y1 - y)));
    return (distance);
}

double getCorrectAngle(double angle)
{
    double normalizedAngle;

    normalizedAngle = 0;
    normalizedAngle = fmod(angle, (M_PI * 2));
    if (angle < 0)
        normalizedAngle = angle + (M_PI * 2);
    return (normalizedAngle);
}

double    castRay(double rayAngle, t_intersection_data *data, t_global_state *state)
{
    double horizontalDistance;
    double verticalDistance;
    double rayDistance;

    horizontalDistance = 0.0;
    verticalDistance = 0.0;
    rayDistance = 0.0;
    getHorzIntersection(getCorrectAngle(rayAngle), data, state);
    getVertIntersection(getCorrectAngle(rayAngle), data, state);
    if (data->wallHorzIntesected)
        horizontalDistance = calculateDistance(state->player->initx, state->player->inity, data->wallHorzHitX, data->wallHorzHitY);
    else
        horizontalDistance = INT_MAX;
    if (data->wallVertIntesected)
        verticalDistance = calculateDistance(state->player->initx, state->player->inity, data->wallVertHitX, data->wallVertHitY);
    else
        verticalDistance = INT_MAX;
    if (verticalDistance > horizontalDistance)
    {
        data->wasIntersectionVertical = false;
        rayDistance = horizontalDistance;
        data->wallHitX = data->wallHorzHitX;
        data->wallHitY = data->wallHorzHitY;
    }
    else
    {
        data->wasIntersectionVertical = true;
        rayDistance = verticalDistance;
        data->wallHitX = data->wallVertHitX;
        data->wallHitY = data->wallVertHitY;
    }

    if (data->wasIntersectionVertical)
         txtOffsetX =  fmod(data->wallHitY , w);
    else
         txtOffsetX =  fmod(data->wallHitX , w);
    // printf("%f\n", rayAngle);
    // printf("%f\n", deg_to_radian(state->player->v_angle));
    // if (radian_to_deg(rayAngle) == state->player->v_angle)
    //     data->projectPlaneDistance = rayDistance;
    // (void)rayDistance;
    //TODO: Draw a line in the canvas using the wallHitX and wallHitY
    DDA(state->player->initx, state->player->inity, data->wallHitX, data->wallHitY, state);
    return (rayDistance * cos(deg_to_radian(state->player->v_angle) - rayAngle));
    // Here will be the code that will be responsible for casting one ray.
}

void    getHorzIntersection(double rayAngle, t_intersection_data *data, t_global_state *state)
{
    int tileY = state->data->tileY;

    data->wallHorzIntesected = false;
    data->yintercept = floor(state->player->inity / tileY) * tileY;
    if (rayFacingDown(rayAngle))
        data->yintercept += tileY;
    data->xintercept = state->player->initx + ((data->yintercept - state->player->inity) / tan(rayAngle));
    
    data->ystep = tileY;
    if (!rayFacingDown(rayAngle))
        data->ystep *= -1;

    data->xstep = data->ystep / tan(rayAngle);
    if (rayFacingLeft(rayAngle) && data->xstep > 0)
        data->xstep *= -1;
    if (rayFacingRight(rayAngle) && data->xstep < 0)
        data->xstep *= -1;

    data->nextHorzTouchX = data->xintercept;
    data->nextHorzTouchY = data->yintercept;
    if (rayFacingUp(rayAngle))
        data->nextHorzTouchY -= 1;
    while (data->nextHorzTouchX >= 0 && data->nextHorzTouchX <= state->data->window_width && data->nextHorzTouchY >= 0 && data->nextHorzTouchY <= state->data->window_height)
    {
        if (checkCoordinatesWall(data->nextHorzTouchX, data->nextHorzTouchY, state))
        {
            data->wallHorzIntesected = true;
            if (rayFacingUp(rayAngle))
                data->nextHorzTouchY += 1;
            data->wallHorzHitX = data->nextHorzTouchX;
            data->wallHorzHitY = data->nextHorzTouchY;
            // DDA(state->player->initx, state->player->inity, data->wallHorzHitX, data->wallHorzHitY, state);
            break;
        }
        else
        {
            data->nextHorzTouchX += data->xstep;
            data->nextHorzTouchY += data->ystep;
        }
    }

    // for (int i = ((int)data->xintercept - 4); i < (int)data->xintercept; i++)
    // {
    //     my_mlx_pixel_put(state , i , (int)data->yintercept, 0x00FF0000, NULL);
    // }
    // for (int i = ((int)data->xintercept + data->xstep - 4); i < (int)data->xintercept + data->xstep; i++)
    // {
    //     my_mlx_pixel_put(&state->img , i , (int)data->yintercept + data->ystep, 0x00FF0000);
    // }
    // for (int i = ((int)data->xintercept + (data->xstep * 2) - 4); i < (int)data->xintercept + (data->xstep * 2); i++)
    // {
    //     my_mlx_pixel_put(&state->img , i , (int)data->yintercept + (data->ystep * 2), 0x00FF0000);
    // }
}

void    getVertIntersection(double rayAngle, t_intersection_data *data, t_global_state *state)
{
    int tileX = state->data->tileX;

    data->wallVertIntesected = false;
    data->xintercept = floor(state->player->initx / tileX) * tileX;
    if (rayFacingRight(rayAngle))
        data->xintercept += tileX;
    data->yintercept = state->player->inity + ((data->xintercept - state->player->initx) * tan(rayAngle));
    
    data->xstep = tileX;
    if (rayFacingLeft(rayAngle))
        data->xstep *= -1;

    data->ystep = data->xstep * tan(rayAngle);
    if (rayFacingUp(rayAngle) && data->ystep > 0)
        data->ystep *= -1;
    if (rayFacingDown(rayAngle) && data->ystep < 0)
        data->ystep *= -1;
    data->nextVertTouchX = data->xintercept;
    data->nextVertTouchY = data->yintercept;
    if (rayFacingLeft(rayAngle))
        data->nextVertTouchX -= 1;
    while (data->nextVertTouchX >= 0 && data->nextVertTouchX <= state->data->window_width && data->nextVertTouchY >= 0 && data->nextVertTouchY <= state->data->window_height)
    {
        if (checkCoordinatesWall(data->nextVertTouchX, data->nextVertTouchY, state))
        {
            data->wallVertIntesected = true;
            if (rayFacingLeft(rayAngle))
                data->nextVertTouchX += 1;
            data->wallVertHitX = data->nextVertTouchX;
            data->wallVertHitY = data->nextVertTouchY;
            // for (int i = ((int)data->nextVertTouchX - 4); i < (int)data->nextVertTouchX; i++)
            // {
            //     my_mlx_pixel_put(&state->img , i + 2 , (int)data->nextVertTouchY, 0x00FF0000);
            // }
            // DDA(state->player->initx, state->player->inity, data->wallVertHitX, data->wallVertHitY, state);
            break;
        }
        else
        {
            data->nextVertTouchX += data->xstep;
            data->nextVertTouchY += data->ystep;
        }
    }
    // printf("xintercept: %f\n", data->xintercept);
    // printf("yintercept: %f\n", data->yintercept);

    // for (int i = ((int)data->yintercept - 4); i < (int)data->yintercept; i++)
    // {
    //     my_mlx_pixel_put(&state->img , (int)data->xintercept, i, 0x00FF0000);
    // }
    // for (int i = ((int)data->yintercept + (int)data->ystep - 4); i < (int)data->yintercept + (int)data->ystep; i++)
    // {
    //     my_mlx_pixel_put(&state->img , (int)data->xintercept + (int)data->xstep, i, 0x00FF0000);
    // }
    //  for (int i = ((int)data->yintercept + ((int)data->ystep * 2) - 4); i < (int)data->yintercept + ((int)data->ystep * 2); i++)
    // {
    //     my_mlx_pixel_put(&state->img , (int)data->xintercept + ((int)data->xstep * 2), i, 0x00FF0000);
    // }
}

void    raycaster(t_global_state *state)
{
    int columnId;
    int raysNumber;
    double rayAngle;
    t_intersection_data *data;
    double distance_to_pp;
    double rayDistance;
    double colHeight;
   

    printf("TileX: %d\n", state->data->tileX);
    printf("TileY: %d\n", state->data->tileY);
    columnId = 0;
    colHeight = 0;
    rayDistance = 0;
    distance_to_pp = 0;
    raysNumber = state->data->window_width / 1;
    rayAngle = deg_to_radian(state->player->v_angle) - (FEILD_OF_VIEW_ANGLE / 2.0);
    distance_to_pp = (state->data->window_width / 2)  / (tan(FEILD_OF_VIEW_ANGLE / 2.0));
    // printf("Number of rays: %d\n", raysNumber);

    // printf("Player angle: %f\n", deg_to_radian(state->player->v_angle));
    // printf("Ray angle •: %f\n", deg_to_radian(state->player->v_angle) - FEILD_OF_VIEW_ANGLE);
    // printf("Ray angle in rad: %f\n", FEILD_OF_VIEW_ANGLE);
    data = (t_intersection_data *)malloc(sizeof(t_intersection_data));
    data->projectPlaneDistance = 0;
    if (!data)
        return ;
    printf("Project plane dis: %f\n", distance_to_pp);
    testing_img.img  = mlx_new_image (state->vars->mlx, state->data->window_width, state->data->window_height);
    testing_img.addr = (int *)mlx_get_data_addr (testing_img.img, &(testing_img.bits_per_pixel), &(testing_img.line_length), &(testing_img.endian));
    color(state, 0x0016213E, state->data->window_height / 2);
    color(state, 0x00C3F8FF, 0);
    while (columnId < raysNumber)
    {

        //? Debugging purposes.
        getHorzIntersection(getCorrectAngle(rayAngle), data, state);
        getVertIntersection(getCorrectAngle(rayAngle), data, state);
        // double x = state->player->initx + cos(rayAngle) * 50;
        // double y = state->player->inity + sin(rayAngle) * 50;
        // DDA(state->player->initx, state->player->inity, x, y, state);
        rayDistance =  castRay(rayAngle, data, state);
        //printf("Ray distance: %f\n", rayDistance);
        colHeight = (state->data->tileY / rayDistance) * distance_to_pp;
        //printf("col height: %f\n", colHeight);
        rayAngle += FEILD_OF_VIEW_ANGLE / raysNumber;
        draw_column (columnId * RAY_THICKNESS, ((state->data->window_height / 2) - (colHeight / 2)), 0x00ff0165,state, colHeight);
        columnId += 1;
    }
}


//?DONE: Create Cast ray function that will cast only one ray based on 
//?DONE: Create a function that will calculate the distance between two dots
//?DONE: Create a function that will round the angle
//?DONE: Caluculate horizontal interections: getHorzIntersection
//?DONE: Caluculate vertical interections: getVertIntersection
//?DONE: Get where the ray is facing
//?DONE: Create a function that will check that the current x and y position are a wall or not