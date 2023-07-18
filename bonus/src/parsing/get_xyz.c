/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xyz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 03:07:16 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/07 06:34:16 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_xyz(char *xyz_str, double *xyz)
{
	char	**xyz_arr;

	xyz_arr = ft_split(xyz_str, ',');
	if (cnt_arr_num(xyz_arr) != 3)
		format_error();
	xyz[0] = str_to_double(xyz_arr[0]);
	xyz[1] = str_to_double(xyz_arr[1]);
	xyz[2] = str_to_double(xyz_arr[2]);
	free_arr(xyz_arr);
}

void	get_xyz_from_to(char *xyz_str, double from, double to, double *xyz)
{
	char	**xyz_arr;

	xyz_arr = ft_split(xyz_str, ',');
	if (cnt_arr_num(xyz_arr) != 3)
		format_error();
	xyz[0] = str_to_double(xyz_arr[0]);
	xyz[1] = str_to_double(xyz_arr[1]);
	xyz[2] = str_to_double(xyz_arr[2]);
	check_range(xyz[0], from, to);
	check_range(xyz[1], from, to);
	check_range(xyz[2], from, to);
	free_arr(xyz_arr);
}
