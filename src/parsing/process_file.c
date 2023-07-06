/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:52:02 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/07 03:43:03 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include "scene.h"

static void	is_valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3 || ft_strncmp(&filename[len - 3], ".rt", 3) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		exit(1);
	}
}

void	foo()
{
	return ;
}

void	normalize_rgb(double *rgb)
{
	rgb[0] /= 255;
	rgb[1] /= 255;
	rgb[2] /= 255;
}

void	put_ambient_info(char **line_arr, t_scene *scene)
{
	double	ka;
	double	rgb[3];

	if (cnt_arr_num(line_arr) != 3)
		format_error();
	if (!is_double(line_arr[1]))
		format_error();
	ka = str_to_double(line_arr[1]);
	check_range(ka, 0, 1);
	get_xyz_from_to(line_arr[2], 0, 255, rgb);
	normalize_rgb(rgb);
	scene->ambient = vmult_(color3(rgb[0], rgb[1], rgb[2]), ka);
}

void	put_camera_info(char **line_arr, t_scene *scene)
{
	double	xyz[3];
	double	fov;

	if (cnt_arr_num(line_arr) != 4)
		format_error();
	get_xyz(line_arr[1], xyz);
	scene->camera.origin = point3(xyz[0], xyz[1], xyz[2]);
	get_xyz_from_to(line_arr[2], -1, 1, xyz);
	scene->camera.norm_orient = vec3(xyz[0], xyz[1], xyz[2]);
	if (!is_double(line_arr[3]))
		format_error();
	fov = str_to_double(line_arr[3]);
	check_range(fov, 0, 180);
	scene->camera.fov = fov;
}

void	put_light_info(char **line_arr, t_scene *scene)
{
	double	origin[3];
	double	brightness;

	if (cnt_arr_num(line_arr) != 3)
		format_error();
	get_xyz(line_arr[1], origin);
	if (!is_double(line_arr[2]))
		format_error();
	brightness = str_to_double(line_arr[2]);
	check_range(brightness, 0, 1);
	scene->light = object(LIGHT_POINT, \
	light_point(point3(origin[0], origin[1], origin[2]), \
	color3(1, 1, 1), brightness), color3(0, 0, 0));
}

void	put_info_from_line_arr(char **line_arr, t_scene *scene)
{
	if (ft_strncmp(line_arr[0], "A", 2) == 0)
		put_ambient_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "C", 2) == 0)
		put_camera_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "L", 2) == 0)
		put_light_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "sp", 3) == 0)
		foo();
	else if (ft_strncmp(line_arr[0], "pl", 3) == 0)
		foo();
	else if (ft_strncmp(line_arr[0], "cy", 3) == 0)
		foo();
	else
		format_error();
}

void	process_lines_from_file(int fd, t_scene *scene)
{
	char	*line;
	char	**line_arr;

	line = get_next_line(fd);
	while (line)
	{
		line_arr = split_line(line, ' ');
		if (!line_arr)
		{
			perror("split_line");
			exit(1);
		}
		if (!line_arr[0])
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		put_info_from_line_arr(line_arr, scene);
		free_arr(line_arr);
		free(line);
		line = get_next_line(fd);
	}
}

void	process_file(char *filename, t_scene *scene)
{
	int		fd;

	is_valid_filename(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nopen");
		exit(1);
	}
	process_lines_from_file(fd, scene);
	close(fd);
}
