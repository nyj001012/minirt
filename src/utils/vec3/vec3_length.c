/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:42:37 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 13:43:03 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief t_vec3의 길이를 제곱한다.
 * @param vec
 * @return double 벡터 길이의 제곱
 */
double	vlength2(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

/**
 * @brief t_vec3의 길이를 구한다.
 * @param vec
 * @return double 벡터 길이
 */
double	vlength(t_vec3 vec)
{
	return (sqrt(vlength2(vec)));
}
