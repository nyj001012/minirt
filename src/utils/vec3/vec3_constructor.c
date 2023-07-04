/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:32:38 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 13:33:15 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief t_vec3 생성자
 * @param x
 * @param y
 * @param z
 * @return t_vec3 생성된 벡터
 */
t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/**
 * @brief t_point3 생성자
 * @param x
 * @param y
 * @param z
 * @return t_point3 생성된 점의 좌표
 */
t_point3	point3(double x, double y, double z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

/**
 * @brief t_color3 생성자
 * @param r
 * @param g
 * @param b
 * @return t_color3 생성된 색상값
 */
t_point3	color3(double r, double g, double b)
{
	t_color3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

/**
 * @brief t_vec3의 x, y, z 값을 설정한다.
 * @param vec
 * @param x
 * @param y
 * @param z
 */
void	vset(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
