/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:05:40 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 04:00:07 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_bonus.h"
#include "trace_bonus.h"
#include "utils_bonus.h"

/**
 * @brief 원뿔과 광선의 교점을 구한다.
 * @see https://github.com/miniRT-jiphyeonjeon/MiniRT/wiki/Cone
 * @param cn
 * @param ray
 * @param eq
 */
void	calculate_cn_equation(t_cone *cn, t_ray *ray, t_equation *eq)
{
	t_vec3	oc;
	double	r_div_h;

	oc = vminus(ray->origin, cn->center);
	r_div_h = cn->radius / cn->height;
	eq->a = vdot(ray->direction, ray->direction)
		- (1 + pow(r_div_h, 2))
		* pow(vdot(ray->direction, cn->axis), 2);
	eq->half_b = vdot(ray->direction, oc)
			+ r_div_h * cn->radius * vdot(ray->direction, cn->axis)
			- (1 + pow(r_div_h, 2))
			* vdot(oc, cn->axis)
			* vdot(ray->direction, cn->axis);
	eq->c = vdot(oc, oc)
			+ 2 * cn->radius * r_div_h * vdot(oc, cn->axis)
			- (1 + pow(r_div_h, 2))
			* pow(vdot(oc, cn->axis), 2)
			- cn->radius_square;
	eq->discriminant = pow(eq->half_b, 2) - eq->a * eq->c;
	eq->min_root = (-eq->half_b - sqrt(eq->discriminant)) / eq->a;
	eq->max_root = (-eq->half_b + sqrt(eq->discriminant)) / eq->a;
}

t_bool	hit_cone_side(t_cone *cn, t_ray *ray, t_hit_record *rec, double root)
{
	double	hit_height;
	t_vec3	q;

	if (root < rec->tmin || root > rec->tmax || isnan(root))
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	hit_height = vdot(vminus(rec->p, cn->center), cn->axis);
	if (hit_height < 0 || hit_height > cn->height)
		return (FALSE);
	hit_height = cn->height - hit_height;
	q = vunit(
			vminus(rec->p,
				vplus(cn->center,
					vmult_(cn->axis,
						vdot(vminus(rec->p, cn->center),
					cn->axis)))));
	rec->normal = vunit(vplus(vmult_(cn->axis, cn->radius * hit_height / cn->height),
				vmult_(q, hit_height)));
	set_face_normal(ray, rec);
	return (TRUE);
}

t_bool	hit_cone(t_object *cn_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone		*cn;
	t_equation	eq;

	rec->albedo = cn_obj->albedo;
	cn = cn_obj->element;
	calculate_cn_equation(cn, ray, &eq);
	if (eq.discriminant < 0)
		return (FALSE);
	if (hit_cone_side(cn, ray, rec, eq.min_root))
		return (TRUE);
	if (hit_cone_side(cn, ray, rec, eq.max_root))
		return (TRUE);
	return (FALSE);
}
