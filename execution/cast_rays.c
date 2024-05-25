/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:17:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/25 17:12:30 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

// first horizental intersec:
/*
	y = floor(p_y / TILE_SIZE) * TILE_SIZE
	x = p_x + (p_y - y / tan(angle))
*/

// horizental intersec steps
/*
	step_y = opposite = TILE_SIZE
	step_x = opposite / tan(angle)
*/
void	h_intersec(t_cub *cub)
{
	double		start_x;
	double		start_y;
	double		step_x;
	double		step_y;
	t_player	*p;

	p = cub->p;
	start_y = floor(p->y_pixel / TILE_SIZE) * TILE_SIZE;
	start_x = p->x_pixel + (p->y_pixel - start_y / tan(cub->ray->ray_angle));
	step_y = TILE_SIZE;
	step_x = step_y / tan(cub->ray->ray_angle);
	
	
}

// first horizental intersec:
/*
	x = floor(p_x / TILE_SIZE) * TILE_SIZE
	y = p_y - ((x - p_x) * tan(angle))
*/

// horizental intersec steps
/*
	step_x = adjacent = TILE_SIZE
	step_y = opposite * tan(angle)
*/
void	v_intersec(t_cub *cub, int first)
{
	double		start_x;
	double		start_y;
	double		step_x;
	double		step_y;
	t_player	*p;

	p = cub->p;
	start_x = floor(p->x_pixel / TILE_SIZE) * TILE_SIZE;
	start_y = p->y_pixel - ((start_x - p->x_pixel) * tan(cub->ray->ray_angle));
	step_x = TILE_SIZE;
	step_y = step_x * tan(cub->ray->ray_angle);
	
}

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
