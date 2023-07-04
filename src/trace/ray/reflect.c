/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:31:00 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 13:31:42 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"
/**
 * @brief 벡터 v를 법선 벡터 n에 대해 반사 시킨 벡터를 반환 한다.
 * v - 2 * dot(v, n) * n
 * @param v
 * @param n
 * @return
 */
t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vminus(v, vmult_(n, vdot(v, n) * 2)));
}
