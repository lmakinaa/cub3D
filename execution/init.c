/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:41:45 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 02:42:23 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(t_map *map_data)
{
	t_data	*res;
	int		i;

	res = heap_control(M_ALLOC, sizeof(t_data), 0, 1);
	res->map_2d = map_data->map;
	res->cub = heap_control(M_ALLOC, sizeof(t_cub), 0, 1);
	res->p_x = map_data->p_y;
	res->p_y = map_data->p_x;
	res->h_map = map_data->height;
	res->w_map = map_data->width;
	res->sky_c = get_rgba(map_data->C[0], map_data->C[1], map_data->C[2], 100);
	res->floor_c = get_rgba(map_data->F[0], map_data->F[1],
			map_data->F[2], 100);
	return (res);
}

void	init_the_player(t_cub *cub)
{
	cub->p->x_pixel = cub->data->p_x * TILE_SIZE + TILE_SIZE / 2;
	cub->p->y_pixel = cub->data->p_y * TILE_SIZE + TILE_SIZE / 2;
	cub->p->fov_rd = (FOV * M_PI) / 180;
	cub->p->angle = M_PI / 2;
	cub->ray->n_rays = (float) N_RAYS;
}
