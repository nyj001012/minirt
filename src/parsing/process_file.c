/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:52:02 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/07 06:16:04 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	is_unique_acl(int *acl, char *identifier)
{
	if (ft_strncmp(identifier, "A", 2) == 0)
	{
		if (acl[0] == 0)
			++acl[0];
		else
			format_error();
	}
	else if (ft_strncmp(identifier, "C", 2) == 0)
	{
		if (acl[1] == 0)
			++acl[1];
		else
			format_error();
	}
	else if (ft_strncmp(identifier, "L", 2) == 0)
	{
		if (acl[2] == 0)
			++acl[2];
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
	else if (ft_strncmp(line_arr[0], "L", 2) == 0)
		put_light_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "sp", 3) == 0)
		put_sphere_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "pl", 3) == 0)
		put_plane_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "cy", 3) == 0)
		put_cylinder_info(line_arr, scene);
	else
		format_error();
}

void	process_lines_from_file(int fd, t_scene *scene)
{
	char		*line;
	char		**line_arr;
	static int	acl[3];

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
		if (!line_arr[0])
		{
			line = get_next_line(fd);
			continue ;
		}
		put_info_from_line_arr(line_arr, scene, acl);
		free_arr(line_arr);
		line = get_next_line(fd);
	}
	if (acl[0] != 1 || acl[1] != 1 || acl[2] != 1)
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
	process_lines_from_file(fd, scene);
	close(fd);
}
