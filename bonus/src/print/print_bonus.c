/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:00:47 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 00:01:21 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/print_bonus.h"

/**
 * @deprecated 사용하지 않음
 * @brief 색상값 출력
 * [0,1] 로  되어있는 RGB 값을 각각 [0,255]에 맵핑해서 출력
 * @param pixel_color 
 */
void	write_color(t_color3 pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
		(int)(255.999 * pixel_color.y),
		(int)(255.999 * pixel_color.z));
}
