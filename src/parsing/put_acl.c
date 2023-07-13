/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_acl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 06:11:46 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/10 15:04:31 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	put_ambient_info(char **line_arr, t_scene *scene)
{
	double	ka;
	double	rgb[3];

	if (cnt_arr_num(line_arr) != 3)
		format_error();
	ka = str_to_double(line_arr[1]);
	check_range(ka, 0, 1);
	get_xyz_from_to(line_arr[2], 0, 255, rgb);
	normalize_rgb(rgb);
	scene->ambient = vmult_(color3(rgb[0], rgb[1], rgb[2]), ka);
}

void	put_camera_info(char **line_arr, t_scene *scene)
{
	double	point[3];
	double	orient[3];
	t_vec3	orient_vec;
	double	fov;

	if (cnt_arr_num(line_arr) != 4)
		format_error();
	get_xyz(line_arr[1], point);
	get_xyz_from_to(line_arr[2], -1, 1, orient);
	orient_vec = vunit(vec3(orient[0], orient[1], orient[2]));
	fov = str_to_double(line_arr[3]);
	check_range(fov, 0, 180);
	scene->canvas = canvas(1280, 720);
	scene->camera = camera(&scene->canvas, \
	point3(point[0], point[1], point[2]), orient_vec, fov);
}

void	put_light_info(char **line_arr, t_scene *scene)
{
	double	origin[3];
	double	brightness;

	if (cnt_arr_num(line_arr) != 3)
		format_error();
	get_xyz(line_arr[1], origin);
	brightness = str_to_double(line_arr[2]);
	check_range(brightness, 0, 1);
	scene->light = object(LIGHT_POINT, \
	light_point(point3(origin[0], origin[1], origin[2]), \
	color3(1, 1, 1), brightness), color3(0, 0, 0));
}
