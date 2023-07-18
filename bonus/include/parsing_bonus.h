/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:51:12 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/18 23:28:25 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"
# include "utils.h"
# include "scene.h"
# include <fcntl.h>
# include <stdio.h>

t_bool	is_double(char *str);
double	str_to_double(char *str);
void	free_arr(char **arr);
int		cnt_arr_num(char **arr);
void	check_range(double num, double from, double to);
void	format_error(void);
void	normalize_rgb(double *rgb);
void	put_ambient_info(char **line_arr, t_scene *scene);
void	put_camera_info(char **line_arr, t_scene *scene);
void	put_light_info(char **line_arr, t_scene *scene);
void	put_sphere_info(char **line_arr, t_scene *scene);
void	put_plane_info(char **line_arr, t_scene *scene);
void	put_cylinder_info(char **line_arr, t_scene *scene);
void	put_cone_info(char **line_arr, t_scene *scene);
void	get_xyz(char *xyz_str, double *xyz);
void	get_xyz_from_to(char *xyz_str, double from, double to, double *xyz);
char	**split_line(char const *s, char c);
void	process_file(char *filename, t_scene *scene);

#endif