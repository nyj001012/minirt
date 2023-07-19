/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create_bonus2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:45:50 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:09:58 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"

/**
 * @brief cone을 동적 할당하는 생성자
 * @param center
 * @param radius
 * @param height
 * @return t_cone*
 */
t_cone	*cone(t_point3 center, t_vec3 axis, double radius, double height)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->center = center;
	cone->axis = axis;
	cone->radius = radius;
	cone->radius_square = radius * radius;
	cone->height = height;
	return (cone);
}
