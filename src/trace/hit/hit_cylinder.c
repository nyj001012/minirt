/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:00:59 by yena              #+#    #+#             */
/*   Updated: 2023/07/17 13:15:28 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

void	calculate_cy_equation(t_cylinder *cy, t_ray *ray, t_equation *eq)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;

	oc = vminus(ray->origin, cy->center);
	a = vdot(ray->direction, ray->direction)
		- pow(vdot(ray->direction, cy->axis), 2);
	half_b = vdot(ray->direction, oc) - vdot(oc, cy->axis)
		* vdot(ray->direction, cy->axis);
	c = vdot(oc, oc) - pow(vdot(oc, cy->axis), 2) - pow(cy->diameter / 2.0, 2);
	eq->a = a;
	eq->half_b = half_b;
	eq->c = c;
	eq->discriminant = pow(eq->half_b, 2) - eq->a * eq->c;
}

t_bool	get_cy_root(t_equation *eq)
{
	eq->discriminant = pow(eq->half_b, 2) - eq->a * eq->c;
	if (eq->discriminant < 0)
		return (FALSE);
	eq->min_root = (-eq->half_b - sqrt(eq->discriminant)) / eq->a;
	eq->max_root = (-eq->half_b + sqrt(eq->discriminant)) / eq->a;
	return (TRUE);
}

t_bool	check_hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec, double root)
{
	double	hit_height;
	
	if (root < rec->tmin || root > rec->tmax || isnan(root))
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	hit_height = vdot(vminus(rec->p, cy->center), cy->axis);
	if (hit_height < 0 || hit_height > cy->height)
		return (FALSE);
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
	t_equation	eq;
	t_cylinder	*cy;

	cy = cy_obj->element;
	calculate_cy_equation(cy, ray, &eq);
	if (get_cy_root(&eq) == FALSE)
		return (FALSE);
	if (!check_hit_cylinder(cy, ray, rec, eq.min_root)
		&& !check_hit_cylinder(cy, ray, rec, eq.max_root))
		return (FALSE);
	rec->normal = vunit(
		vminus(rec->p,
			vplus(cy->center,
				vmult_(cy->axis,
					vdot(vminus(rec->p, cy->center), cy->axis)))));
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (TRUE);
}
