/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 02:42:18 by jihyeole          #+#    #+#             */
/*   Updated: 2023/07/19 00:00:50 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
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

void	check_range(double num, double from, double to)
{
	if (num < from || num > to)
		format_error();
}

void	format_error(void)
{
	ft_putstr_fd("Error\nInvalid data format in the file\n", 2);
	exit(1);
}

void	normalize_rgb(double *rgb)
{
	rgb[0] /= 255;
	rgb[1] /= 255;
	rgb[2] /= 255;
}
