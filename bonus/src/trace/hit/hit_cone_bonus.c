/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 00:05:40 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 01:27:39 by yena             ###   ########.fr       */
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
	double	h_div_r;

	oc = vminus(ray->origin, cn->center);
	h_div_r = cn->height / cn->radius;
	eq->a = vdot(ray->direction, ray->direction)
		- (1 + pow(h_div_r, 2))
		* pow(vdot(ray->direction, cn->axis), 2);
	eq->half_b = vdot(ray->direction, oc)
			+ pow(h_div_r * cn->radius, 2) * vdot(ray->direction, cn->axis)
			- (1 + pow(h_div_r, 2))
			* vdot(oc, cn->axis)
			* vdot(ray->direction, cn->axis);
	eq->c = vdot(oc, oc)
			+ 2 * cn->radius * h_div_r * vdot(oc, cn->axis)
			- (1 + pow(h_div_r, 2))
			* pow(vdot(oc, cn->axis), 2)
			- cn->radius_square;
	eq->discriminant = pow(eq->half_b, 2) - eq->a * eq->c;
	eq->min_root = (-eq->half_b - sqrt(eq->discriminant)) / eq->a;
	eq->max_root = (-eq->half_b + sqrt(eq->discriminant)) / eq->a;
}

t_bool	hit_cone_side(t_cone *cn, t_ray *ray, t_hit_record *rec, double root)
{
	double	hit_height;
	t_vec3	ph;

	if (root < rec->t_min || root > rec->t_max || isnan(root))
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	hit_height = vdot(vminus(rec->p, cn->center), cn->axis);
	if (hit_height < 0 || hit_height > cn->height)
		return (FALSE);
	ph = vunit(
			vminus(rec->p,
				vplus(cn->center,
					vmult_(cn->axis,
						vdot(vminus(rec->p, cn->center),
					cn->axis)))));
	rec->normal = vunit(vplus(vmult_(cn->normal, cn->radius * hit_height / co->height),
				vmult_(ph, hit_height)));
	set_face_normal(ray, rec);
	return (TRUE);
}

t_bool	hit_cone(t_object *cn_obj, t_ray *ray, t_hit_record *rec)
{
	t_cone		*cn;
	t_equation	eq;

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
