/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:04:10 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/15 20:26:27 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

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
