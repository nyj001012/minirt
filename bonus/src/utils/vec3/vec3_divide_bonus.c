/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_divide_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:06:06 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:46:14 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

/**
 * @brief t_vec3와 double 값의 나눗셈을 구한다.
 * @param vec
 * @param t
 * @return t_vec3 벡터 / 스칼라
 */
t_vec3	vdivide_(t_vec3 vec, double t)
{
	vec.x *= 1 / t;
	vec.y *= 1 / t;
	vec.z *= 1 / t;
	return (vec);
}
