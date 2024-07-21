/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:41:45 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 05:26:15 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_p_angle(t_cub *cub)
{
	if (cub->parsing->player == 'E')
		cub->p->angle = 2 * M_PI;
	else if (cub->parsing->player == 'W')
		cub->p->angle = M_PI;
	else if (cub->parsing->player == 'S')
		cub->p->angle = M_PI / 2;
	else if (cub->parsing->player == 'N')
		cub->p->angle = (3 * M_PI) / 2;
}

t_data	*init_data(t_map *map_data)
{
	t_data	*res;

	res = heap_control(M_ALLOC, sizeof(t_data), 0, 1);
	res->map_2d = map_data->map;
	res->cub = heap_control(M_ALLOC, sizeof(t_cub), 0, 1);
	res->p_x = map_data->p_y;
	res->p_y = map_data->p_x;
	res->h_map = map_data->height;
	res->w_map = map_data->width;
	res->sky_c = get_rgba(map_data->ceil[0], map_data->ceil[1],
			map_data->ceil[2], 100);
	res->floor_c = get_rgba(map_data->floor[0], map_data->floor[1],
			map_data->floor[2], 100);
	res->cub->parsing = map_data;
	return (res);
}

void	init_the_player(t_cub *cub)
{
	cub->p->x_pixel = cub->data->p_x * TILE_SIZE + TILE_SIZE / 2;
	cub->p->y_pixel = cub->data->p_y * TILE_SIZE + TILE_SIZE / 2;
	cub->p->fov_rd = (FOV * M_PI) / 180;
	cub->ray->n_rays = (float) N_RAYS;
}
