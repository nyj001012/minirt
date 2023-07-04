/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/03 20:01:21 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

/**
 * @brief 근의 공식을 이용해 t를 구하는 함수, 즉 빛과 물체가 교차하는지 확인한다.
 * 짝수 근의 공식 판별식: b^2 - ac
 * 작은 근이 tmin보다 작거나 큰 근이 tmax보다 크면 교차하지 않음
 * @param ray
 * @param sp
 * @param discriminant
 * @param root
 * @return t_bool 교차 여부
 */
t_bool	is_valid_hit(t_ray *ray, t_sphere *sp, double *discriminant,
					double *root)
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		sqrt_d;

	oc = vminus(ray->origin, sp->center);
	a = vlength2(ray->direction);
	half_b = vdot(oc, ray->direction);
	c = vlength2(oc) - sp->radius_square;
	*discriminant = half_b * half_b - a * c;
	if (*discriminant < 0)
		return (FALSE);
	sqrt_d = sqrt(*discriminant);
	root = (-half_b - sqrt_d) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrt_d) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief 구와 광선의 교차 여부를 판단하는 함수
 * 구의 방정식: (x - C) * (x - C) = r^2
 * 광선의 방정식: P(t) = A + tb
 * 광선의 방정식을 구의 방정식에 대입해서 근의 공식을 이용해 t를 구함
 * t가 0보다 크면 구와 광선이 교차함
 * @param sp_obj
 * @param ray
 * @param rec
 * @return t_bool 교차 여부
 */
t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
	double		discriminant;
	double		sqrt_d;
	double		root;

	sp = sp_obj->element;
	if (!is_valid_hit(ray, sp, &discriminant, &sqrt_d))
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide_(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}
