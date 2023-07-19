/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:06:06 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 16:00:55 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_BONUS_H
# define MLX_UTILS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include "structures_bonus.h"

# define ESC 53

void	initialize_mlx_info(t_mlx_info *mlx_info);
int		key_hook(int keycode, t_mlx_info *mlx_info);
int		destroy_window(t_mlx_info *mlx_info);
#endif
