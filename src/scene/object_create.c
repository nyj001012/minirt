/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 13:47:42 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "scene.h"

/**
 * @brief object를 동적 할당하는 생성자
 * object의 멤버변수 값을 초기화하는 매개변수 생성자
 * @param type 
 * @param element 
 * @param albedo 
 * @return t_object* 
 */
t_object	*object(t_object_type type, void *element, t_color3 albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->albedo = albedo;
	new->element = element;
	new->next = NULL;
	return (new);
}

/**
 * @brief sphere를 동적 할당하는 생성자
 * sphere의 멤버변수 값을 초기화하는 매개변수 생성자
 * @param center 
 * @param radius 
 * @return t_sphere* 
 */
t_sphere	*sphere(t_point3 center, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->radius = radius;
	sphere->radius_square = radius * radius;
	return (sphere);
}

/**
 * @brief light_point를 동적 할당하는 생성자
 * light_point의 멤버변수를 초기화하는 매개변수 생성자
 * @param light_origin 
 * @param light_color 
 * @param bright_ratio 
 * @return t_light* 
 */
t_light	*light_point(t_point3 light_origin, t_color3 light_color,
				double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}
