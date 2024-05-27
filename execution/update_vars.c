/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/27 18:17:30 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	p_movemenet(t_cub *cub, int *new_x, int *new_y)
{
	int	step;

	if (cub->p->l_r == 1)
	{
		step = PLAYER_SPEED;
		(*new_x) = roundf(cub->p->mini_x_pixel + cos(cub->p->angle) * step);
		(*new_y) = roundf(cub->p->mini_y_pixel - sin(cub->p->angle) * step);
	}
	else if (cub->p->l_r == -1)
	{
		step = PLAYER_SPEED;
		(*new_x) = roundf(cub->p->mini_x_pixel - cos(cub->p->angle) * step);
		(*new_y) = roundf(cub->p->mini_y_pixel + sin(cub->p->angle) * step);
	}
	else if (cub->p->u_d != 0)
	{
		step = cub->p->u_d * PLAYER_SPEED;
		(*new_x) = roundf(cub->p->mini_x_pixel + cos(cub->p->angle) * step);
		(*new_y) = roundf(cub->p->mini_y_pixel + sin(cub->p->angle) * step);
	}
}

void	update_vars(t_cub *cub)
{
	int new_x;
	int new_y;
	int	tmp_x;
	int	tmp_y;

	cub->p->angle = map_angle(cub->p->angle + cub->p->rot * ROTATION_SPEED);
	p_movemenet(cub, &new_x, &new_y);
	tmp_x = new_x / MINI_TILE_SIZE;
	tmp_y = new_y / MINI_TILE_SIZE;
	if (cub->data->map2d[tmp_y][tmp_x] != '1')
	{
		tmp_x = (new_x + MINI_TILE_SIZE / 2) / MINI_TILE_SIZE;
		tmp_y = (new_y + MINI_TILE_SIZE / 2) / MINI_TILE_SIZE;
		if (cub->data->map2d[tmp_y][tmp_x] != '1')
		{
			(1) && (cub->p->mini_x_pixel = new_x, cub->p->mini_y_pixel = new_y);
			(1) && (cub->p->x_pixel = new_x, cub->p->y_pixel = new_y);
		}
	}
}
