/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:30:37 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 15:44:53 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	main(void)
{
	t_mlx_info	mlx_info;

	initialize_mlx_info(&mlx_info);
	mlx_key_hook(mlx_info.mlx_window, key_hook, &mlx_info);
	mlx_mou(mlx_info.mlx);
	return (0);
}
