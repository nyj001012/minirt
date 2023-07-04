/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:30:37 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 16:28:10 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include "scene.h"

int	main(void)
{
	t_mlx_info	mlx_info;
	t_scene		*scene;

	initialize_mlx_info(&mlx_info);
	// TODO => 파싱으로부터 구조체 반환 받고 진행
	mlx_info.scene = scene_init();
	mlx_key_hook(mlx_info.mlx_window, key_hook, &mlx_info);
	mlx_hook(mlx_info.mlx_window, 17, 0, destroy_window, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}
