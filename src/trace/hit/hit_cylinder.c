/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:00:59 by yena              #+#    #+#             */
/*   Updated: 2023/07/12 15:37:29 by yena             ###   ########.fr       */
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
	t_vec3		center;
	t_vec3		oc;
	double		root;

	cy = cy_obj->element;
	if (top_or_bottom == TOP)
		center = vplus_(cy->center, 0, 0, cy->height / 2.0);
	else
		center = vplus_(cy->center, 0, 0, (cy->height / 2.0) * -1);
	oc = vminus(ray->origin, center);
	root = vdot(oc, cy->axis) / vdot(ray->direction, cy->axis);
	if (fabs(root) > cy->diameter / 2.0)
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
 * 짝수 근의 공식을 이용하여 원기둥과 광선의 교차 여부를 판단한다.
 * @param a
 * @param half_b
 * @param c
 * @param rec
 * @return
 */
double	get_cy_root(double a, double half_b, double sqrt_d, t_hit_record *rec)
{
	double	root;

	root = (-half_b - sqrt_d) / a;
	if (root < rec->tmin || rec->tmax < root)
		root = (-half_b + sqrt_d) / a;
	return (root);
}

/**
 * @brief 원기둥과 광선의 교차 여부를 판단하는 함수
 * 원기둥의 방정식: ((ray - cy_obj->center) * (cy_obj * axis)) ^ 2 = r^2.
 * 즉, 원기둥의 중심에서 광선이 hit한 지점으로 향하는 벡터와 원기둥의 축이 뚜껑으로 이루는 평면에
 * 수직인 벡터의 내적이 원기둥의 반지름의 제곱과 같다.
 * 광선의 방정식: ray(t) = A + tB. (A: 광선의 원점, B: 광선의 방향)
 * 광선의 방정식을 원기둥의 방정식에 대입하여 광선이 원기둥에 닿는지 확인한다.
 * @param ray
 * @param cy
 * @param discriminant
 * @param rec
 * @return
 */
double	get_cy_discriminant_and_root(t_ray *ray, t_cylinder *cy,
					double *discriminant, t_hit_record *rec)
{
	t_vec3	cross_micro_o;
	t_vec3	cross_pe_o;
	double	a;
	double	half_b;
	double	c;

	cross_micro_o = vcross(ray->direction, cy->axis);
	cross_pe_o = vcross(vminus(ray->origin, cy->center), cy->axis);
	a = vlength2(cross_micro_o);
	half_b = vdot(cross_micro_o, cross_pe_o);
	c = vlength2(cross_pe_o) - pow(cy->diameter / 2.0, 2);
	*discriminant = pow(half_b, 2) - a * c;
	if (*discriminant < 0)
		return (0);
	return (get_cy_root(a, half_b, sqrt(*discriminant), rec));
}

/**
 * @brief 원기둥의 옆면과 광선의 교차 여부를 판단하는 함수
 * 광선의 방정식을 원기둥의 방정식에 대입하여 광선이 원기둥의 옆면에 닿는지 확인한다.
 * @param cy_obj
 * @param ray
 * @param rec
 * @return
 */
t_bool	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double		discriminant;
	double		root;

	cy = cy_obj->element;
	root = get_cy_discriminant_and_root(ray, cy, &discriminant, rec);
	if (discriminant < 0)
		return (FALSE);
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide_(vminus(rec->p, cy->center), cy->diameter / 2.0);
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
	if (hit_cylinder_cap(cy_obj, ray, rec, TOP))
		return (TRUE);
	if (hit_cylinder_side(cy_obj, ray, rec))
		return (TRUE);
	if (hit_cylinder_cap(cy_obj, ray, rec, BOTTOM))
		return (TRUE);
	return (FALSE);
}
