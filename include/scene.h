/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/07 05:06:28 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_scene		*scene_init(t_mlx_info mlx_info);
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 origin, t_vec3 norm_orient,
				double fov);
t_object	*object(t_object_type type, void *element, t_color3 albedo);
t_sphere	*sphere(t_point3 cneter, double radius);
t_plane		*plane(t_point3 point, t_vec3 normal_vector);
t_cylinder	*cylinder(t_point3 center, t_vec3 axis, double diameter,
				double height);
t_light		*light_point(t_point3 light_origin, t_color3 light_color,
				double bright_ratio);
t_ray		get_primary_ray(t_scene *scene, int i, int j);
void		render_scene(t_mlx_info *mlx_info);

#endif
