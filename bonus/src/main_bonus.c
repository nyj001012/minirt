/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 23:15:25 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:46:48 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils_bonus.h"
#include "scene_bonus.h"
#include "parsing_bonus.h"

int	main(int argc, char *argv[])
{
	t_mlx_info	mlx_info;
	t_scene		scene;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (1);
	}
	process_file(argv[1], &scene);
	initialize_mlx_info(&mlx_info);
	mlx_info.scene = &scene;
	render_scene(&mlx_info);
	mlx_key_hook(mlx_info.mlx_window, key_hook, &mlx_info);
	mlx_hook(mlx_info.mlx_window, 17, 0, destroy_window, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}
