/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:29:56 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:00:45 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "libft.h"
# include "structures_bonus.h"
# include "utils_bonus.h"
# include "scene_bonus.h"
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