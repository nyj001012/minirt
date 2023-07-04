/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:35:49 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 13:36:19 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief t_vec3 끼리의 합을 구한다.
 * @param vec
 * @param vec2
 * @return t_vec3 두 벡터의 합
 */
t_vec3	vplus(t_vec3 vec, t_vec3 vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

/**
 * @brief t_vec3와 double 값의 합을 구한다.
 * @param vec
 * @param x
 * @param y
 * @param z
 * @return t_vec3 벡터와 double 값의 합
 */
t_vec3	vplus_(t_vec3 vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}
