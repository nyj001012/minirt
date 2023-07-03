/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:01:06 by yena              #+#    #+#             */
/*   Updated: 2023/07/03 15:01:07 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

t_bool  hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool          is_hit;
    t_hit_record    temp_rec;

    temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화
    is_hit = FALSE;
    while (world)
    {
        if (hit_obj(world, ray, &temp_rec))
        {
            is_hit = TRUE;
            temp_rec.tmax = temp_rec.t; // 더 멀리 있는 오브젝트에는 히트하지 않게 함
            *rec = temp_rec;
        }
        world = world->next;
    }
    return (is_hit);
}

t_bool  hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool  hit_result;

    hit_result = FALSE;
    if (world->type == SP)
        hit_result = hit_sphere(world->element, ray, rec);
    return (hit_result);
}
