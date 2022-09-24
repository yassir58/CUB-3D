/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:16:25 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/24 19:05:06 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ray_facing_down(double ray_angle)
{
	if (ray_angle > 0 && ray_angle < M_PI)
		return (1);
	return (0);
}

int	ray_facing_right(double ray_angle)
{
	if (ray_angle < (M_PI_2) || ray_angle > (1.5 * M_PI))
		return (1);
	return (0);
}

int	ray_facing_up(double ray_angle)
{
	if (!ray_facing_down(ray_angle))
		return (1);
	return (0);
}

int	ray_facing_left(double ray_angle)
{
	if (!ray_facing_right(ray_angle))
		return (1);
	return (0);
}

double	correct_angle(double angle)
{
	double	normalized_angle;

	normalized_angle = 0;
	if (angle >= 0)
		normalized_angle = fmod(angle, (M_PI * 2));
	else
		normalized_angle = angle + (M_PI * 2);
	return (normalized_angle);
}
