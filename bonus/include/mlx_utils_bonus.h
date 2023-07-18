/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:15:40 by yena              #+#    #+#             */
/*   Updated: 2023/07/19 02:35:22 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include "structures_bonus.h"

# define ESC 53

void	initialize_mlx_info(t_mlx_info *mlx_info);
int		key_hook(int keycode, t_mlx_info *mlx_info);
int		destroy_window(t_mlx_info *mlx_info);
#endif
