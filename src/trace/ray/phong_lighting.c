/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:49:20 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 13:31:15 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

/**
 * @brief 광원과 교점 사이에 다른 물체가 있는지 확인한다.
 * @param objs
 * @param light_ray
 * @param light_len
 * @return t_bool 광원과 교점 사이에 다른 물체가 있으면 TRUE, 없으면 FALSE
 */
t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

/**
 * @brief phong lighting 모델의 diffuse를 계산한다.
 * diffuse = (광원의 색상 * KD) * max(dot(normal, light_dir), 0)
 * @param scene
 * @param light
 * @return t_color3 광원으로부터 교점까지의 거리
 */
t_color3	get_diffuse(t_scene *scene, t_light *light)
{
	t_vec3		light_dir;
	double		light_len;
	t_ray		light_ray;
	double		kd;
	t_color3	diffuse;

	light_dir = vminus(light->origin, scene->rec.p);
	light_len = vlength(light_dir);
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)),
			light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vmult(light->light_color, kd);
	return (diffuse);
}

/**
 * @brief phong lighting 모델의 specular을 계산한다.
 * specular = (광원의 색상 * KS) * (max(dot(view_dir, reflect_dir), 0) ^ KSN)
 * @param scene
 * @param light
 * @return t_color3 광원으로부터 교점까지의 거리
 */
t_color3	get_specular(t_scene *scene, t_light *light)
{
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	t_color3	specular;

	view_dir = vunit(vmult(scene->ray.direction, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), KSN);
	specular = vmult(vmult(light->light_color, KS), spec);
	return (specular);
}

/**
 * @brief 광원으로부터 교점까지의 거리를 계산한다.
 * @param scene
 * @param light
 * @return t_color3 광원으로부터 교점까지의 거리
 */
t_color3	point_light_get(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		brightness;

	diffuse = get_diffuse(scene, light);
	specular = get_specular(scene, light);
	brightness = light->bright_ratio * LUMEN;
	return (vmult(vplus(vplus(diffuse, specular), specular), brightness));
}

/**
 * @brief phong lighting 모델을 사용하여 광원의 색상을 계산한다.
 * 광원의 색상 = (광원의 밝기 * (diffuse + specular)) * albedo
 * @param scene
 * @return t_color3 광원의 색상
 */
t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vplus(light_color,
					point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}
