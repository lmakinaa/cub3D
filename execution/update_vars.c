/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/27 21:21:37 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	p_movement(t_cub *mlx, double move_x, double move_y)
{
	int		new_x;
	int		new_y;

	new_y = roundf(mlx->p->y_pixel + move_y);
	new_x = roundf(mlx->p->x_pixel + move_x);
	if (mlx->data->map2d[new_y / TILE_SIZE][new_x / TILE_SIZE] != '1')
	{
		mlx->p->x_pixel = new_x;
		mlx->p->y_pixel = new_y;
		mlx->p->mini_x_pixel = new_x;
		mlx->p->mini_y_pixel = new_y;
	}
}

void	update_vars(t_cub *cub)
{
	double	tmp_x;
	double	tmp_y;
	double	step;

	cub->p->angle = map_angle(cub->p->angle + cub->p->rot * ROTATION_SPEED);
	step = PLAYER_SPEED;
	if (cub->p->l_r == 1)
	{
		tmp_x = -1 * sin(cub->p->angle) * step;
		tmp_y = cos(cub->p->angle) * step;
	}
	else if (cub->p->l_r == -1)
	{
		tmp_x = sin(cub->p->angle) * step;
		tmp_y = -1 * cos(cub->p->angle) * step;
	}
	else if (cub->p->u_d != 0)
	{
		step *= cub->p->u_d;
		tmp_x = cos(cub->p->angle) * step;
		tmp_y = sin(cub->p->angle) * step;
	}
	p_movement(cub, tmp_x, tmp_y);
}
