/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:01:17 by yena              #+#    #+#             */
/*   Updated: 2023/07/03 20:31:49 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief t_vec3 생성자
 * @param x
 * @param y
 * @param z
 * @return t_vec3 생성된 벡터
 */
t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/**
 * @brief t_point3 생성자
 * @param x
 * @param y
 * @param z
 * @return t_point3 생성된 점의 좌표
 */
t_point3	point3(double x, double y, double z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

/**
 * @brief t_color3 생성자
 * @param r
 * @param g
 * @param b
 * @return t_color3 생성된 색상값
 */
t_point3	color3(double r, double g, double b)
{
	t_color3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

/**
 * @brief t_vec3의 x, y, z 값을 설정한다.
 * @param vec
 * @param x
 * @param y
 * @param z
 */
void	vset(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

/**
 * @brief t_vec3의 길이를 제곱한다.
 * @param vec
 * @return double 벡터 길이의 제곱
 */
double	vlength2(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

/**
 * @brief t_vec3의 길이를 구한다.
 * @param vec
 * @return double 벡터 길이
 */
double	vlength(t_vec3 vec)
{
	return (sqrt(vlength2(vec)));
}

/**
 * @brief t_vec3 끼리의 합을 구한다.
 * @param vec
 * @param vec2
 * @return t_vec3 두 벡터의 합
 */
t_vec3	vplus(t_vec3 vec, t_vec3 vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

/**
 * @brief t_vec3와 double 값의 합을 구한다.
 * @param vec
 * @param x
 * @param y
 * @param z
 * @return t_vec3 벡터와 double 값의 합
 */
t_vec3	vplus_(t_vec3 vec, double x, double y, double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

/**
 * @brief t_vec3 끼리의 차를 구한다.
 * @param vec
 * @param vec2
 * @return t_vec3 두 벡터의 차
 */
t_vec3	vminus(t_vec3 vec, t_vec3 vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}

/**
 * @brief t_vec3와 double 값의 차를 구한다.
 * @param vec
 * @param x
 * @param y
 * @param z
 * @return t_vec3 벡터와 double 값의 차
 */
t_vec3	vminus_(t_vec3 vec, double x, double y, double z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);
}

/**
 * @brief t_vec3와 double 값의 곱을 구한다.
 * @param vec
 * @param t
 * @return t_vec3 벡터 * 스칼라
 */
t_vec3	vmult(t_vec3 vec, double t)
{
	vec.x *= t;
	vec.y *= t;
	vec.z *= t;
	return (vec);
}

/**
 * @brief t_vec3 끼리의 곱을 구한다.
 * @param vec
 * @param vec2
 * @return t_vec3 두 벡터의 곱
 */
t_vec3	vmult_(t_vec3 vec, t_vec3 vec2)
{
	vec.x *= vec2.x;
	vec.y *= vec2.y;
	vec.z *= vec2.z;
	return (vec);
}

/**
 * @brief t_vec3와 double 값의 나눗셈을 구한다.
 * @param vec
 * @param t
 * @return t_vec3 벡터 / 스칼라
 */
t_vec3	vdivide(t_vec3 vec, double t)
{
	vec.x *= 1 / t;
	vec.y *= 1 / t;
	vec.z *= 1 / t;
	return (vec);
}

/**
 * @brief t_vec3 끼리의 내적을 구한다.
 * @param vec
 * @param vec2
 * @return double 두 벡터의 내적
 */
double	vdot(t_vec3 vec, t_vec3 vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

/**
 * @brief t_vec3 끼리의 외적을 구한다.
 * @param vec
 * @param vec2
 * @return t_vec3 두 벡터의 외적
 */
t_vec3	vcross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	new;

	new.x = vec.y * vec2.z - vec.z * vec2.y;
	new.y = vec.z * vec2.x - vec.x * vec2.z;
	new.z = vec.x * vec2.y - vec.y * vec2.x;
	return (new);
}

/**
 * @brief t_vec3의 단위 벡터를 구한다.
 * @param vec
 * @return t_vec3 단위 벡터
 */
t_vec3	vunit(t_vec3 vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
	{
		printf("Error\n:Devider is 0");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

/**
 * @brief 두 벡터의 요소를 비교하여 각각 작은 값을 반환한다.
 * @param vec1
 * @param vec2
 * @return t_vec3 두 벡터의 각각 작은 값
 */
t_vec3	vmin(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}
