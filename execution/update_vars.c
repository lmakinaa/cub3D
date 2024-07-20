/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 01:23:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/20 21:54:11 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ix_wall(t_cub *cub, double start_y, double start_x)
{
	int	y;
	int	x;
 
 if (start_y < 0 || start_x < 0 || start_x > S_W || start_y > S_H)
		return (1);
	x = (start_x) / TILE_SIZE;
	y = (start_y) / TILE_SIZE;


if (y >= cub->data->h_map || x >= cub->data->w_map)
		return (1);
	if (cub->data->map_2d[y][x] == '1')
		return (1);
	if (cub->ray->distance_to_wall == 0)
		return (1);
	// x = (start_x + TILE_SIZE/4) / TILE_SIZE;
	// y = (start_y + TILE_SIZE/4) / TILE_SIZE;
	// if (y >= cub->data->h_map ||  x >= cub->data->w_map)
	// 	return (1);
	// if (cub->data->map_2d[y][x] == '1')
	// 	return (1);
	return (0);
}
void	p_movement(t_cub *mlx, double move_x, double move_y)
{
	int		new_x;
	int		new_y;

	new_y = mlx->p->y_pixel + (move_y * 5);
	new_x = mlx->p->x_pixel + (move_x * 5);
	if (!ix_wall(mlx, new_y, new_x))
	{
		mlx->p->x_pixel += move_x;
		mlx->p->y_pixel += move_y;
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
		tmp_x = sin(cub->p->angle) * step * -1;
		tmp_y = cos(cub->p->angle) * step;
	}
	else if (cub->p->l_r == -1)
	{
		tmp_x = sin(cub->p->angle) * step;
		tmp_y = cos(cub->p->angle) * step * -1;
	}
	else if (cub->p->u_d != 0)
	{
		step *= cub->p->u_d;
		tmp_x = cos(cub->p->angle) * step;
		tmp_y = sin(cub->p->angle) * step;
	}
	p_movement(cub, tmp_x, tmp_y);
}
