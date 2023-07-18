/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:29:39 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 02:36:27 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"
#include "trace_bonus.h"
#include "mlx.h"

/**
 * @brief 캔버스의 픽셀에 해당하는 레이를 구한다.
 * @param scene
 * @param i
 * @param j
 * @return t_ray 캔버스의 픽셀에 해당하는 레이
 */
t_ray	get_primary_ray(t_scene *scene, int i, int j)
{
	double	u;
	double	v;
	t_ray	ray;

	u = (double)i / (scene->canvas.width - 1);
	v = (double)j / (scene->canvas.height - 1);
	ray = ray_primary(&scene->camera, u, v);
	return (ray);
}

/**
 * @brief t_scene의 캔버스와 물체를 렌더링한다.
 * @param mlx_info
 */
void	render_scene(t_mlx_info *mlx_info)
{
	int			i;
	int			j;
	t_color3	pixel_color;
	t_scene		*scene;

	scene = mlx_info->scene;
	i = -1;
	while (++i < scene->canvas.height)
	{
		j = -1;
		while (++j < scene->canvas.width)
		{
			scene->ray = get_primary_ray(scene, j, i);
			pixel_color = ray_color(scene);
			mlx_pixel_put(mlx_info->mlx,
				mlx_info->mlx_window,
				j,
				scene->canvas.height - (i + 1),
				t_color3_to_int(pixel_color));
		}
	}
}
