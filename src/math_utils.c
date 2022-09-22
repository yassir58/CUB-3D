/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:17:07 by ochoumou          #+#    #+#             */
/*   Updated: 2022/09/22 13:17:08 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double deg_to_radian (int deg)
{
    return (deg * (M_PI / 180));
}

int radian_to_deg(double rad)
{
    return ((rad / M_PI) * 180);
}