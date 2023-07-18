/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:00:59 by yena              #+#    #+#             */
/*   Updated: 2023/07/18 15:04:45 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_bonus.h"
#include "trace_bonus.h"
#include "utils_bonus.h"

/**
 * @brief 원기둥의 방정식과 광선의 방정식을 연립하여 근의 공식에 이용할 a, b/2, c를 구한다.
 * @see https://github.com/miniRT-jiphyeonjeon/MiniRT/wiki/Cylinder
 * @param cy 
 * @param ray 
 * @param eq 
 */
void	calculate_cy_equation(t_cylinder *cy, t_ray *ray, t_equation *eq)
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	t_point3	underside_center;

	underside_center = vminus(cy->center, vmult_(cy->axis, cy->height / 2));
	oc = vminus(ray->origin, underside_center);
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

/**
 * @brief 근의 공식을 이용하여 원기둥 방정식과 광선의 방정식을 연립한 식의 해를 구한다.
 * @param eq 
 * @return t_bool 
 */
t_bool	get_cy_root(t_equation *eq)
{
	eq->discriminant = pow(eq->half_b, 2) - eq->a * eq->c;
	if (eq->discriminant < 0)
		return (FALSE);
	eq->min_root = (-eq->half_b - sqrt(eq->discriminant)) / eq->a;
	eq->max_root = (-eq->half_b + sqrt(eq->discriminant)) / eq->a;
	return (TRUE);
}

/**
 * @brief root의 값이 유효한지 확인한 후, 광선이 원기둥에 닿은 곳의 위치가
 * 원기둥의 높이 내인지 확인한다.
 * @param cy 
 * @param ray 
 * @param rec 
 * @param root 
 * @return t_bool 
 */
t_bool	check_hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec,
						double root)
{
	double		hit_height;
	t_point3	underside_center;

	underside_center = vminus(cy->center, vmult_(cy->axis, cy->height / 2));
	if (root < rec->tmin || root > rec->tmax || isnan(root))
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	hit_height = vdot(vminus(rec->p, underside_center), cy->axis);
	if (hit_height < 0 || hit_height > cy->height)
		return (FALSE);
	return (TRUE);
}

t_bool	hit_cylinder_side(t_cylinder *cy, t_ray *ray, t_hit_record *rec,
	t_equation	*eq)
{
	t_point3	underside_center;
	t_bool		hit;

	underside_center = vminus(cy->center, vmult_(cy->axis, cy->height / 2));
	hit = FALSE;
	calculate_cy_equation(cy, ray, eq);
	if (get_cy_root(eq) == FALSE)
		return (FALSE);
	if (check_hit_cylinder(cy, ray, rec, eq->min_root))
	{
		eq->root = eq->min_root;
		hit = TRUE;
	}
	if (check_hit_cylinder(cy, ray, rec, eq->min_root))
	{
		eq->root = eq->max_root;
		hit = TRUE;
	}
	if (!hit)
		return (FALSE);
	rec->normal = vunit(vminus(rec->p, vplus(underside_center, vmult_(cy->axis,
						vdot(vminus(rec->p, underside_center), cy->axis)))));
	set_face_normal(ray, rec);
	return (hit);
}

/**
 * @brief 원기둥과 광선의 교차 여부를 판단한다.
 * @param cy_obj 
 * @param ray 
 * @param rec 
 * @return t_bool 
 */
t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_equation	eq;
	t_cylinder	*cy;
	t_bool		hit;

	cy = cy_obj->element;
	hit = FALSE;
	eq.root = 0;
	if (hit_cylinder_side(cy, ray, rec, &eq))
		hit = TRUE;
	if (hit_cylinder_base(cy, ray, rec, &eq))
	{
		rec->t = eq.root;
		rec->p = ray_at(ray, rec->t);
		rec->normal = cy->axis;
		set_face_normal(ray, rec);
		rec->front_face = TRUE;
		hit = TRUE;
	}
	rec->albedo = cy_obj->albedo;
	return (hit);
}
