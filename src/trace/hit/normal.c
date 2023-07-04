/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:01:09 by yena              #+#    #+#             */
/*   Updated: 2023/07/03 20:03:58 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

/**
 * @brief 법선 벡터를 설정한다.
 * 광선의 방향 벡터와 교점의 법선 벡터의 내적이 음수라면, 광선은 객체의 앞면에 hit.
 * 광선의 앞면에 hit면 그대로, 아니라면 법선을 반대로 뒤집는다.
 * 이는 항상 광선 방향 벡터와 법선 벡터를 반대인 상태로 사용하기 위함이다.
 * @param r
 * @param rec
 */
void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	rec->front_face = vdot(r->direction, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vmult_(rec->normal, -1);
}
