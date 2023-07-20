/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:33:02 by yena              #+#    #+#             */
/*   Updated: 2023/07/20 16:11:34 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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

void	is_unique_acl(int *ac, char *identifier)
{
	if (ft_strncmp(identifier, "A", 2) == 0)
	{
		if (ac[0] == 0)
			++ac[0];
		else
			format_error();
	}
	else if (ft_strncmp(identifier, "C", 2) == 0)
	{
		if (ac[1] == 0)
			++ac[1];
		else
			format_error();
	}
}

void	put_info_from_line_arr(char **line_arr, t_scene *scene, int *acl)
{
	is_unique_acl(acl, line_arr[0]);
	if (ft_strncmp(line_arr[0], "A", 2) == 0)
		put_ambient_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "C", 2) == 0)
		put_camera_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "l", 2) == 0)
		put_light_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "sp", 3) == 0)
		put_sphere_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "pl", 3) == 0)
		put_plane_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "cy", 3) == 0)
		put_cylinder_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "cn", 3) == 0)
		put_cone_info(line_arr, scene);
	else
		format_error();
}

void	process_lines_from_file(int fd, t_scene *scene)
{
	char		*line;
	char		**line_arr;
	static int	ac[2];

	line = get_next_line(fd);
	while (line)
	{
		line_arr = split_line(line, ' ');
		if (!line_arr)
		{
			perror("split_line");
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
		if (!line_arr[0])
		{
			free_arr(line_arr);
			continue ;
		}
		put_info_from_line_arr(line_arr, scene, ac);
		free_arr(line_arr);
	}
	if (ac[0] != 1 || ac[1] != 1)
		format_error();
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
	scene->world = NULL;
	scene->light = NULL;
	process_lines_from_file(fd, scene);
	close(fd);
}
