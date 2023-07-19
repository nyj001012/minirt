/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_object_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:44:03 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:09:15 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	put_sphere_info(char **line_arr, t_scene *scene)
{
	double	xyz[3];
	double	diameter;
	double	rgb[3];

	if (cnt_arr_num(line_arr) != 4)
		format_error();
	get_xyz(line_arr[1], xyz);
	diameter = str_to_double(line_arr[2]);
	if (diameter <= 0)
		format_error();
	get_xyz_from_to(line_arr[3], 0, 255, rgb);
	normalize_rgb(rgb);
	oadd(&scene->world, object(SP, sphere(point3(xyz[0], xyz[1], xyz[2]), \
	diameter), color3(rgb[0], rgb[1], rgb[2])));
}

void	put_plane_info(char **line_arr, t_scene *scene)
{
	double	xyz[3];
	double	normal[3];
	t_vec3	normal_vec;
	double	rgb[3];

	if (cnt_arr_num(line_arr) != 4)
		format_error();
	get_xyz(line_arr[1], xyz);
	get_xyz_from_to(line_arr[2], -1, 1, normal);
	normal_vec = vunit(vec3(normal[0], normal[1], normal[2]));
	get_xyz_from_to(line_arr[3], 0, 255, rgb);
	normalize_rgb(rgb);
	oadd(&scene->world, object(PL, plane(point3(xyz[0], xyz[1], xyz[2]), \
	normal_vec), color3(rgb[0], rgb[1], rgb[2])));
}

void	put_cylinder_info(char **line_arr, t_scene *scene)
{
	double	center[3];
	double	axis[3];
	double	diameter;
	double	height;
	double	rgb[3];

	if (cnt_arr_num(line_arr) != 6)
		format_error();
	get_xyz(line_arr[1], center);
	get_xyz_from_to(line_arr[2], -1, 1, axis);
	diameter = str_to_double(line_arr[3]);
	if (diameter <= 0)
		format_error();
	height = str_to_double(line_arr[4]);
	if (height <= 0)
		format_error();
	get_xyz_from_to(line_arr[5], 0, 255, rgb);
	normalize_rgb(rgb);
	oadd(&scene->world, object(CY, \
	cylinder(point3(center[0], center[1], center[2]), \
	vunit(vec3(axis[0], axis[1], axis[2])), diameter, height), \
	color3(rgb[0], rgb[1], rgb[2])));
}

void	put_cone_info(char **line_arr, t_scene *scene)
{
	double	center[3];
	double	axis[3];
	double	radius;
	double	height;
	double	rgb[3];

	if (cnt_arr_num(line_arr) != 6)
		format_error();
	get_xyz(line_arr[1], center);
	get_xyz_from_to(line_arr[2], -1, 1, axis);
	radius = str_to_double(line_arr[3]) / 2;
	if (radius <= 0.0)
		format_error();
	height = str_to_double(line_arr[4]);
	if (height <= 0.0)
		format_error();
	get_xyz_from_to(line_arr[5], 0, 255, rgb);
	normalize_rgb(rgb);
	oadd(&scene->world, object(CN,
			cone(point3(center[0], center[1], center[2]),
				vunit(vec3(axis[0], axis[1], axis[2])),
				radius,
				height),
			color3(rgb[0], rgb[1], rgb[2])));
}
