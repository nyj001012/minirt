/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:01:06 by yena              #+#    #+#             */
/*   Updated: 2023/07/12 02:51:12 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

/**
 * @brief 레이가 오브젝트에 히트하는지 확인
 * 각 오브젝트에 대해 hit_obj 함수를 호출하여 히트 여부를 확인
 * @param world
 * @param ray
 * @param rec
 * @return
 */
t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			is_hit;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	is_hit = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec))
		{
			is_hit = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (is_hit);
}

/**
 * @brief 오브젝트에 히트하는지 확인
 * 오브젝트의 타입에 따라 각 오브젝트에 대한 히트 여부를 확인
 * @param world
 * @param ray
 * @param rec
 * @return
 */
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	return (hit_result);
}
