/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:23:18 by yena              #+#    #+#             */
/*   Updated: 2023/07/03 15:01:01 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"
#include "utils.h"

t_bool  hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp;
    t_vec3		oc; // 방향벡터로 나타낸 구의 중심
    double		a;
    double		half_b;
    double		c;
    double		discriminant;
    double		sqrtd;
    double		root;

	sp = sp_obj->element;
    oc = vminus(ray->origin, sp->center);
    a = vlength2(ray->direction);
    half_b = vdot(oc, ray->direction);
    c = vlength2(oc) - sp->radius_square;
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (FALSE);
    sqrtd = sqrt(discriminant);
    // 두 실근(t) 중 tmin과 tmax 사이에 근이 있는지 작은 근부터 체크
    root = (-half_b - sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < rec->tmin || rec->tmax < root)
            return (FALSE);
    }
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 법선 벡터 정규화
    set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 bool로 저장
	rec->albedo = sp_obj->albedo;
    return (TRUE);
}