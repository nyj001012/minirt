/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color3_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:40:12 by yena              #+#    #+#             */
/*   Updated: 2023/07/04 16:43:16 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

/**
 * @brief t_color3 값을 0xTTRRGGBB 형태의 int 값으로 변환한다.
 * @param color
 * @return int 0xTTRRGGBB
 */
int	t_color3_to_int(t_color3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * color.x);
	g = (int)(255.999 * color.y);
	b = (int)(255.999 * color.z);
	return (r << 16 | g << 8 | b);
}
