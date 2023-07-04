/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:52:02 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/05 04:46:10 by jihyeole         ###   ########.fr       */
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

void	free_arr(char **line_arr)
{
	int	i;

	i = 0;
	while (line_arr[i])
	{
		free(line_arr[i]);
		++i;
	}
	free(line_arr);
}

void foo()
{
	return ;
}

void	put_ambient_info(char **line_arr, t_scene *scene)
{
	// 추가하기 
	(void)line_arr;
	(void)scene;
}

int	cnt_arr_num(char **arr)
{
	int	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		++i;
	return (i);
}

void	format_error(void)
{
	ft_putstr_fd("Error\nInvalid data format in the file\n", 2);
	exit(1);
}

void	put_camera_info(char **line_arr, t_scene *scene)
{
	char	**xyz_arr;
	// double	xyz[3];

	(void)scene;
	if (cnt_arr_num(line_arr) != 4)
		format_error();
	xyz_arr = ft_split(line_arr[1], ',');
	if (cnt_arr_num(xyz_arr) != 3)
		format_error();
	free(xyz_arr);
}

void	put_info_from_line_arr(char **line_arr, t_scene *scene)
{
	if (ft_strncmp(line_arr[0], "A", 2) == 0)
		put_ambient_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "C", 2) == 0)
		put_camera_info(line_arr, scene);
	else if (ft_strncmp(line_arr[0], "L", 2) == 0)
		foo();
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
