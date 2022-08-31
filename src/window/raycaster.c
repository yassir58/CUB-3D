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

int checkCoordinatesWall(int x, int y, t_game_data *data)
{
    char **map;

    map = convert_lines_table(data->lines);
    if (map[x][y] == '1')
        return (1);
    return (0);
}

double calculateDistance(int x, int y, int x1, int y1)
{
    double distance;

    distance = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    return (distance);
}

double getCorrectAgnle(double angle)
{
    double normalizedAngle;

    normalizedAngle = 0;
    normalizedAngle = angle % (M_PI * 2);
    if (angle < 0)
        normalizedAngle = angle + (M_PI * 2);
    return (normalizedAngle);
}


void    raycaster(t_game_data *data)
{
    //! TODO: Do all the caculation related to casting rays.
}

int main(void)
{
    printf("%f\n", getCorrectAgnle(-46));
    return (0);
}

//?DONE: Create a function that will calculate the distance between two dots
//?DONE: Create a function that will round the angle
//TODO: Caluculate horizontal interections
//TODO: Caluculate vertical interections
//?DONE: Get where the ray is facing
//?DONE: Create a function that will check that the current x and y position are a wall or not