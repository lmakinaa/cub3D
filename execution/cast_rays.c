/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:17:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/25 01:17:17 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void cast_rays(t_cub *cub, int x, int y)
{
	int	col;

	cub->ray->ray_angle = cub->p->angle - (cub->p->fov_rd / 2);
	col = -1;
	while (++col < cub->ray->n_rays)
	{
		double ray_x = 0;
        double ray_y = 0;
		while (1)
		{
			ray_x += cos(cub->ray->ray_angle) * 0.1;
            ray_y += sin(cub->ray->ray_angle) * 0.1;
            int var_x = (x + ray_x) / TILE_SIZE;
            int var_y = (y + ray_y) / TILE_SIZE;
			if (cub->data->map2d[var_y][var_x] != '1')
                continue;
            else
                break;
		}
		draw_line(cub, x, y,
		x + ray_x,
		y + ray_y,
		get_rgba(0, 0, 255, 255));
		cub->ray->ray_angle += (cub->p->fov_rd / cub->ray->n_rays);
	}
}
