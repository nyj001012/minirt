/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:57 by yena              #+#    #+#             */
/*   Updated: 2023/07/03 15:18:56 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scene.h"

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
					cam.origin, vdivide(cam.horizontal, 2)
					), vdivide(cam.vertical, 2)
				), vec3(0, 0, cam.focal_len)
			);
	return (cam);
}
