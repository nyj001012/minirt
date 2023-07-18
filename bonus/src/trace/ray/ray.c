/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyeole <jihyeole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/18 16:57:56 by jihyeole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/trace_bonus.h"

/**
 * @brief 광선을 생성한다.
 * @param origin
 * @param direction
 * @return t_ray 광선
 */
t_ray	ray(t_point3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vunit(direction);
	return (ray);
}

/**
 * @brief 광선의 원점에서 t만큼 떨어진 지점의 좌표를 반환한다.
 * @param ray
 * @param t
 * @return t_point3 광선의 원점에서 t만큼 떨어진 지점의 좌표
 */
t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->origin, vmult_(ray->direction, t));
	return (at);
}

/**
 * @brief left_bottom + u * horizontal + v * vertical - origin의 단위 벡터.
 * 빛이 left_bottom으로부터 u * horizontal 만큼의 거리에서 쏜 것,
 * 그리고 원점에서부터 v * vertical 만큼의 거리에서 쏜 것을 단위 벡터로 표현
 * @param cam 
 * @param u 
 * @param v 
 * @return t_ray 
 */
t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.origin = cam->origin;
	ray.direction = vunit(
			vminus(
				vplus(
					vplus(
						cam->left_bottom, vmult_(cam->horizontal, u)
						),
					vmult_(cam->vertical, v)
					), cam->origin)
			);
	return (ray);
}

/**
 * @brief t_hit_record 구조체를 초기화한다.
 * @return t_hit_record 초기화된 구조체
 */
t_hit_record	record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

/**
 * @brief 광선이 구에 적중하는지에 따라 색상을 반환한다.
 * @param scene
 * @return t_color3 색상
 */
t_color3	ray_color(t_scene *scene)
{
	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
	else
		return (color3(1, 1, 1));
}
