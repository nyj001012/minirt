/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:38:31 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:01:22 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "structures_bonus.h"
# include "utils_bonus.h"

t_scene		*scene_init(t_mlx_info mlx_info);
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 origin, t_vec3 norm_orient,
				double fov);
t_object	*object(t_object_type type, void *element, t_color3 albedo);
t_sphere	*sphere(t_point3 cneter, double radius);
t_plane		*plane(t_point3 point, t_vec3 normal_vector);
t_cylinder	*cylinder(t_point3 center, t_vec3 axis, double diameter,
				double height);
t_cone		*cone(t_point3 center, t_vec3 axis, double radius, double height);
t_light		*light_point(t_point3 light_origin, t_color3 light_color,
				double bright_ratio);
t_ray		get_primary_ray(t_scene *scene, int i, int j);
void		render_scene(t_mlx_info *mlx_info);

#endif
