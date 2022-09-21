#include "../../includes/cub3d.h"

int ray_facing_down(double ray_angle)
{
    if (ray_angle > 0 && ray_angle < M_PI)
        return (1);
    return (0);
}

int ray_facing_right(double ray_angle)
{
    if (ray_angle < (M_PI_2) || ray_angle > (1.5 * M_PI))
        return (1);
    return (0);
}

int ray_facing_up(double ray_angle)
{
    if (!ray_facing_down(ray_angle))
        return (1);
    return (0);
}

int ray_facing_left(double ray_angle)
{
    if (!ray_facing_right(ray_angle))
        return (1);
    return (0);
}

double get_correct_angle(double angle)
{
    double normalizedAngle;

    normalizedAngle = 0;
    if (angle >= 0)
        normalizedAngle = fmod(angle, (M_PI * 2));
    else
        normalizedAngle = angle + (M_PI * 2);
    return (normalizedAngle);
}