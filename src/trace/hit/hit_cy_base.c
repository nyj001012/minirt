/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:04:06 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/18 15:05:57 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

static double	distance(t_point3 a, t_point3 b)
{
	double	result;

	result = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (result);
}

static double	get_cylinder_base_root(t_cylinder *cy, t_ray *ray, t_hit_record *rec,
	t_point3 center)
{
	double		root;
	t_point3	hit_point;

	root = (vdot(center, cy->axis) - vdot(ray->origin, cy->axis))
		/ vdot(ray->direction, cy->axis);
	hit_point = ray_at(ray, root);
	if (distance(hit_point, center) > cy->diameter / 2)
		root = 0;
	if (root < rec->tmin || root > rec->tmax)
		root = 0;
	return (root);
}

t_bool	hit_cylinder_base(t_cylinder *cy, t_ray *ray, t_hit_record *rec,
	t_equation *eq)
{
	t_point3	upside_center;
	t_point3	underside_center;

	upside_center = vplus(cy->center, vmult_(cy->axis, cy->height / 2));
	eq->max_root = get_cylinder_base_root(cy, ray, rec, upside_center);
	if (eq->max_root < eq->root)
		eq->max_root = 0;
	underside_center = vminus(cy->center, vmult_(cy->axis, cy->height / 2));
	eq->min_root = get_cylinder_base_root(cy, ray, rec, underside_center);
	if (eq->min_root < eq->root)
		eq->min_root = 0;
	if (eq->max_root && eq->min_root)
	{
		if (eq->max_root < eq->min_root)
			eq->root = eq->max_root;
		else
			eq->root = eq->min_root;
	}
	else if (eq->max_root)
		eq->root = eq->max_root;
	else if (eq->min_root)
		eq->root = eq->min_root;
	else
		return (FALSE);
	return (TRUE);
}
