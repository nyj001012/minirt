/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 14:14:52 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

/**
 * @brief 실근을 구하는 함수. 두 실근 중 tmin과 tmax 사이에 있는 실근을 구한다.
 * @param half_b
 * @param sqrt_d
 * @param a
 * @param rec
 * @return double 실근
 */
double	get_root(double half_b, double sqrt_d, double a, t_hit_record *rec)
{
	double	root;

	root = (-half_b - sqrt_d) / a;
	if (root < rec->tmin || rec->tmax < root)
		root = (-half_b + sqrt_d) / a;
	return (root);
}

/**
 * @brief 구의 방정식과 광선의 방정식을 이용해 판별식과 실근을 구하는 함수
 * 판별식이 0보다 작으면 실근이 없다.
 * @see https://en.wikipedia.org/wiki/Quadratic_formula
 * @see https://github.com/GaepoMorningEagles/mini_raytracing_in_c
 * @param ray
 * @param sp
 * @param discriminant
 * @param root
 * @return double 실근
 */
double	get_discriminant_and_root(t_ray *ray, t_sphere *sp,
					double *discriminant, t_hit_record *rec)
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
		return (0);
	sqrt_d = sqrt(*discriminant);
	return (get_root(half_b, sqrt_d, a, rec));
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
	double		root;

	sp = sp_obj->element;
	root = get_discriminant_and_root(ray, sp, &discriminant, rec);
	if (discriminant < 0)
		return (FALSE);
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide_(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = sp_obj->albedo;
	return (TRUE);
}
