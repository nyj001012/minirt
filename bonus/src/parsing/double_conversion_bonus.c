/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_conversion_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:38:31 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:06:31 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

t_bool	is_double(char *str)
{
	if (*str == '-' || *str == '+')
		++str;
	if (*str == '.' || ft_strncmp(str, "00", 2) == 0)
		return (FALSE);
	while (*str && *str != '.')
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		++str;
	}
	if (*str == '.')
	{
		++str;
		if (!*str)
			return (FALSE);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		++str;
	}
	return (TRUE);
}

static double	cal_decimal(char *str)
{
	int		idx;
	double	decimal;

	decimal = 0;
	idx = ft_strlen(str) - 1;
	while (idx >= 0)
	{
		decimal += str[idx] - '0';
		decimal /= 10.0;
		--idx;
	}
	return (decimal);
}

double	str_to_double(char *str)
{
	char	**num_arr;
	double	integer;
	double	decimal;

	if (!is_double(str))
		format_error();
	num_arr = ft_split(str, '.');
	if (!num_arr[1])
	{
		free_arr(num_arr);
		return ((double) ft_atoi(str));
	}
	integer = (double) ft_atoi(num_arr[0]);
	decimal = cal_decimal(num_arr[1]);
	free_arr(num_arr);
	if (str[0] == '-')
		return (integer - decimal);
	else
		return (integer + decimal);
}
