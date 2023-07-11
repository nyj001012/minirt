/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:57 by yena              #+#    #+#             */
/*   Updated: 2023/07/12 05:25:31 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scene.h"

/**
 * @brief scene을 초기화한다.
 * 추후 scene에 object와 light를 매개 변수로 받아와 추가할 수 있도록 한다.
 * @param mlx_info
 * @return t_scene* 초기화된 scene
 */
t_scene	*scene_init(t_mlx_info mlx_info)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->canvas = canvas(mlx_info.window_width, mlx_info.window_height);
	scene->camera = camera(&scene->canvas, point3(0, 0, 0), vec3(0, 0, 0), 0.0);
	world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0));
	oadd(&world,
		object(SP, sphere(point3(0, -1000, -0), 995), color3(1, 1, 1)));
	oadd(&world,
		object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
	scene->world = world;
	lights = object(LIGHT_POINT,
			light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5),
			color3(0, 0, 0));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult_(color3(1, 1, 1), ka);
	return (scene);
}

static t_vec3	get_vertical(t_vec3 cam_dir, t_vec3 horizontal, double height)
{
	double	x;
	double	z;

	if (cam_dir.x == 0)
	{
		z = -1 * cam_dir.y / cam_dir.z;
		x = (-1 * horizontal.y - horizontal.z * z) / horizontal.x;
	}
	else
	{
		z = (cam_dir.y * horizontal.x - cam_dir.x * horizontal.y) / \
		(cam_dir.x * horizontal.z - cam_dir.z * horizontal.x);
		x = (-1 * cam_dir.y - cam_dir.z * z) / cam_dir.x;
	}
	return (vmult_(vunit(vec3(x, 1, z)), height));
}

static void	calculate_cam_view(t_camera *cam, t_vec3 norm_orient)
{
	if (norm_orient.x == 0 && norm_orient.z == 0)
	{
		cam->horizontal = vec3(cam->viewport_width, 0, 0);
		cam->vertical = vec3(0, 0, cam->viewport_height);
	}
	else
	{
		cam->horizontal = vmult_(vunit(vec3(norm_orient.z * -1, 0, \
		norm_orient.x)), cam->viewport_width);
		cam->vertical = get_vertical(norm_orient, cam->horizontal, \
		cam->viewport_height);
	}
}

/**
 * @brief 카메라의 위치를 설정하는 함수
 * 카메라의 죄하단의 좌표는
 * (0 - viewport_width / 2 , 0 - viewport_height / 2, 0 - forcal_length) 이다.
 * @param canvas 
 * @param origin 
 * @return t_camera 
 */
t_camera	camera(t_canvas *canvas, t_point3 origin, t_vec3 norm_orient,
				double fov)
{
	t_camera	cam;
	double		viewport_height;
	double		fov_radian;

	viewport_height = 2.0;
	cam.viewport_height = viewport_height;
	cam.viewport_width = viewport_height * canvas->aspect_ratio;
	fov_radian = fov * (M_PI / 180.0);
	cam.origin = origin;
	cam.focal_len = cam.viewport_width / tan(fov_radian / 2.0);
	calculate_cam_view(&cam, norm_orient);
	cam.left_bottom = vminus(
			vminus(
				vminus(
					cam.origin, vdivide_(cam.horizontal, 2)
					), vdivide_(cam.vertical, 2)
				), vec3(0, 0, cam.focal_len)
			);
	return (cam);
}
