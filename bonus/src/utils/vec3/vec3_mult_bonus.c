/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mult_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:06:06 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:46:31 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

/**
 * @brief t_vec3 끼리의 곱을 구한다.
 * @param vec
 * @param vec2
 * @return t_vec3 두 벡터의 곱
 */
t_vec3	vmult(t_vec3 vec, t_vec3 vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

/**
 * @brief t_vec3와 double 값의 곱을 구한다.
 * @param vec
 * @param t
 * @return t_vec3 벡터 * 스칼라
 */
t_vec3	vmult_(t_vec3 vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}
