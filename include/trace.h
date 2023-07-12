/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/12 14:42:12 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"
# include <stdbool.h>
# include <math.h>

# define KSN 64
# define KS 0.5
# define TOP 1
# define BOTTOM 2

t_ray		ray(t_point3 origin, t_vec3 direction);
t_point3	ray_at(t_ray *ray, double t);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color3	ray_color(t_scene *scene);
t_bool		is_valid_hit(t_ray *ray, t_sphere *sp, double *discriminant,
				double *root);
t_bool		hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
double		get_sp_root(double half_b, double sqrt_d, double a,
				t_hit_record *rec);
double		get_sp_discriminant_and_root(t_ray *ray, t_sphere *sp,
				double *discriminant, t_hit_record *rec);
t_bool		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec,
				int top_or_bottom);
t_bool		hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
double		get_cy_root(double a, double half_b, double c, t_hit_record *rec);
double		get_cy_discriminant_and_root(t_ray *ray, t_cylinder *cy,
				double *discriminant, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);
t_color3	get_diffuse(t_scene *scene, t_light *light);
t_color3	get_specular(t_scene *scene, t_light *light);
t_vec3		reflect(t_vec3 v, t_vec3 n);
t_color3	point_light_get(t_scene *scene, t_light *ligth);
t_color3	phong_lighting(t_scene *scene);
t_bool		in_shadow(t_object *objs, t_ray light_ray, double light_len);

#endif
