/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:00:59 by yena              #+#    #+#             */
/*   Updated: 2023/07/12 14:06:28 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

/**
 * @brief 원기둥 뚜껑과 광선의 교차 여부를 판단하는 함수
 * 두 실근 중 tmin과 tmax 사이에 있는 실근을 구하여 광선이 원기둥 뚜껑에 닿는지 확인한다.
 * t = ((C − O) ⋅ N) / D ⋅ N. (C: 원기둥의 중심, O: 광선의 원점, N: 원기둥의 축, D: 광선의 방향)
 * @param cy_obj
 * @param ray
 * @param rec
 * @param top_or_bottom
 * @return
 */
t_bool	hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec,
					int top_or_bottom)
{
	t_cylinder	*cy;
	t_vec3	center;
	t_vec3	oc;
	double	root;

	cy = cy_obj->element;
	if (top_or_bottom == TOP)
		center = vplus_(cy->center, 0, 0, cy->height / 2.0);
	else
		center = vplus_(cy->center, 0, 0, cy->height / -2.0);
	oc = vminus(center, ray->origin);
	root = vdivide(
			vdot(oc, cy->axis),
			vdot(ray->direction, cy->axis));
			)
	if (fabs(root) > cy->radius)
		return (FALSE);
	if (root < rec->tmin || root > rec->tmax)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = vunit(vminus(rec->p, center));
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}

/**
 * @brief 원기둥과 광선의 교차 여부를 판단하는 함수
 * 원기둥의 방정식: ((ray - cy_obj->center) * (cy_obj * axis)) ^ 2 = r^2.
 * 즉, 원기둥의 중심에서 광선이 hit한 지점으로 향하는 벡터와 원기둥의 축이 뚜껑으로 향하는 벡터의
 * 외적 크기는 반지름을 제곱한 것과 같다.
 * t가 0보다 크면 원기둥이 윗부분, 아랫부분, 옆부분 중에 최소한 하나라도 광선과 교차한다.
 * @param cy_obj 
 * @param ray 
 * @param rec 
 * @return t_bool 
 */
t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	// TODO => cylinder의 윗뚜껑, 아랫뚜껑, 옆면에 광선이 적중하면 return true
	if (hit_cylinder_cap(cy_obj, ray, rec, TOP)
		|| hit_cylinder_cap(cy_obj, ray, rec, BOTTOM)
		|| hit_cylinder_side(cy_obj, ray, rec))
		return (TRUE);
	return (FALSE);
}
