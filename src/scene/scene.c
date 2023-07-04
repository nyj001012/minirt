/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:57 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 16:52:58 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scene.h"

/**
 * @brief scene을 초기화한다.
 * 추후 scene에 object와 light를 매개 변수로 받아와 추가할 수 있도록 한다.
 * @param mlx_info
 * @return t_scene* 초기화된 scene
 */
t_scene *scene_init(t_mlx_info mlx_info)
{
	t_scene     *scene;
	t_object    *world;
	t_object    *lights;
	double      ka;

	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->canvas = canvas(mlx_info.window_width, mlx_info.window_height);
	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
	oadd(&world, object(SP, sphere(point3(0, -1000, -0), 995), color3(1, 1, 1)));
	oadd(&world, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult_(color3(1, 1, 1), ka);
	return (scene);
}

/**
 * @brief 카메라의 위치를 설정하는 함수
 * 카메라의 죄하단의 좌표는
 * (0 - viewport_width / 2 , 0 - viewport_height / 2, 0 - forcal_length) 이다.
 * @param canvas 
 * @param origin 
 * @return t_camera 
 */
t_camera	camera(t_canvas *canvas, t_point3 origin)
{
	t_camera	cam;
	double		focal_len;
	double		viewport_height;

	viewport_height = 2.0;
	focal_len = 1.0;
	cam.origin = origin;
	cam.viewport_height = viewport_height;
	cam.viewport_width = viewport_height * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = vec3(cam.viewport_width, 0, 0);
	cam.vertical = vec3(0, cam.viewport_height, 0);
	cam.left_bottom = vminus(
			vminus(
				vminus(
					cam.origin, vdivide_(cam.horizontal, 2)
					), vdivide_(cam.vertical, 2)
				), vec3(0, 0, cam.focal_len)
			);
	return (cam);
}
