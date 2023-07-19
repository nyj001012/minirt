/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:15:25 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:11:22 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_bonus.h"
#include "trace_bonus.h"
#include "utils_bonus.h"

t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	double	root;

	pl = pl_obj->element;
	root = (vdot(pl->point, pl->normal_vector) - \
	vdot(ray->origin, pl->normal_vector)) \
	/ vdot(ray->direction, pl->normal_vector);
	if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	rec->normal = pl->normal_vector;
	set_face_normal(ray, rec);
	rec->front_face = TRUE;
	rec->albedo = pl_obj->albedo;
	return (TRUE);
}
