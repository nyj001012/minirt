/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 16:25:53 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_scene		*scene_init(void);
t_canvas	canvas(int width, int height);
t_camera	camera(t_canvas *canvas, t_point3 origin);
t_object	*object(t_object_type type, void *element, t_color3 albedo);
t_sphere	*sphere(t_point3 cneter, double radius);
t_light		*light_point(t_point3 light_origin, t_color3 light_color,
				double bright_ratio);

#endif
