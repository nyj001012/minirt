/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:10:50 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 15:51:48 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

/**
 * @brief mlx_info를 동적 할당 없이 초기화한다.
 * @param mlx_info
 */
void	initialize_mlx_info(t_mlx_info *mlx_info)
{
	mlx_info->mlx = mlx_init();
	mlx_info->window_width = 1280;
	mlx_info->window_height = 720;
	mlx_info->mlx_window = mlx_new_window(mlx_info->mlx,
			mlx_info->window_width,
			mlx_info->window_height,
			"minirt");
}

/**
 * @brief 키보드를 누르면 그에 맞는 동작을 수행한다.
 * @details esc 키를 누르면 창을 닫고 프로그램을 종료한다.
 * @param keycode
 * @param mlx_info
 * @return int 0
 */
int	key_hook(int keycode, t_mlx_info *mlx_info)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->mlx_window);
		exit(0);
	}
	return (0);
}

/**
 * @brief 창의 x 버튼을 누르면 창을 닫고 프로그램을 종료한다.
 * @param mlx_info
 * @return int 0
 */
int	destroy_window(t_mlx_info *mlx_info)
{
	mlx_destroy_window(mlx_info->mlx, mlx_info->mlx_window);
	exit(0);
}
