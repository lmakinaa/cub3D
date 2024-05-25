/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/24 02:06:45 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_vars(t_cub *cub)
{
	int	step;
	int new_x;
	int new_y;
	int	tmp_x;
	int	tmp_y;

	cub->p->angle = map_angle(cub->p->angle + cub->p->l_r * ROTATION_SPEED);
	step = cub->p->u_d * PLAYER_SPEED;
	new_x = cub->p->mini_x_pixel + cos(cub->p->angle) * step;
	new_y = cub->p->mini_y_pixel + sin(cub->p->angle) * step;
	tmp_x = new_x / MINI_TILE_SIZE;
	tmp_y = new_y / MINI_TILE_SIZE;
	if (cub->data->map2d[tmp_y][tmp_x] != '1')
		(1) && (cub->p->mini_x_pixel = new_x, cub->p->mini_y_pixel = new_y);
}
