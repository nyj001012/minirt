/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 02:51:12 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/07 03:15:19 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"
# include <fcntl.h>
# include <stdio.h>

t_bool	is_double(char *str);
double	str_to_double(char *str);
void	free_arr(char **arr);
int		cnt_arr_num(char **arr);
void	check_range(double num, double from, double to);
void	format_error(void);
void	get_xyz(char *xyz_str, double *xyz);
void	get_xyz_from_to(char *xyz_str, double from, double to, double *xyz);
char	**split_line(char const *s, char c);
void	process_file(char *filename, t_scene *scene);

#endif