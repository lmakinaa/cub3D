/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:17:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 04:18:52 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_intersec(t_ray *ray, int step, double *n_x, double *n_y)
{
	if (ray->for_norm)
	{
		if (!step)
			(ray->facing_u_d) && ((*n_y) += TILE_SIZE);
		else if (step)
		{
			(!ray->facing_u_d) && ((*n_y) *= -1);
			(!ray->facing_l_r && (*n_x) > 0) && ((*n_x) *= -1);
			(ray->facing_l_r && (*n_x) < 0) && ((*n_x) *= -1);
		}
	}
	else
	{
		if (!step)
			(ray->facing_l_r) && ((*n_x) += TILE_SIZE);
		else if (step)
		{
			(!ray->facing_l_r) && ((*n_x) *= -1);
			(!ray->facing_u_d && (*n_y) > 0) && ((*n_y) *= -1);
			(ray->facing_u_d && (*n_y) < 0) && ((*n_y) *= -1);
		}
	}
}

int	is_wall(t_cub *cub, double start_y, double start_x)
{
	int	y;
	int	x;

	if (start_y < 0 || start_x < 0)
		return (1);
	x = (start_x) / TILE_SIZE;
	y = (start_y) / TILE_SIZE;
	if (y >= cub->data->h_map || x >= cub->data->w_map)
		return (1);
	if (cub->data->map_2d[y][x] == '1')
		return (1);
	return (0);
}

// first horizental intersec:
/*
	y = floor(p_y / TILE_SIZE) * TILE_SIZE
	x = p_x + (y - p_y / tan(angle))
*/

// horizental intersec steps
/*
	step_y = opposite = TILE_SIZE
	step_x = opposite / tan(angle)
*/
double	h_intersec_distance(t_cub *cub, double ray_angle)
{
	double		start_x;
	double		start_y;
	double		step_x;
	double		step_y;
	double		d;

	start_y = floor(cub->p->y_pixel / TILE_SIZE) * TILE_SIZE;
	cub->ray->for_norm = 1;
	adjust_intersec(cub->ray, 0, NULL, &start_y);
	start_x = cub->p->x_pixel
		+ ((start_y - cub->p->y_pixel) / tan(ray_angle));
	step_y = TILE_SIZE;
	step_x = TILE_SIZE / tan(ray_angle);
	adjust_intersec(cub->ray, 1, &step_x, &step_y);
	while (start_x >= 0 && start_y >= 0)
	{
		if ((!cub->ray->facing_u_d && is_wall(cub, start_y - 1, start_x))
			|| is_wall(cub, start_y, start_x))
			break ;
		start_y += step_y;
		start_x += step_x;
	}
	d = sqrt(pow(start_x - cub->p->x_pixel, 2)
			+ pow(start_y - cub->p->y_pixel, 2));
	return (cub->ray->h_x = start_x, cub->ray->h_y = start_y, d);
}

// first vertical intersec:
/*
	x = floor(p_x / TILE_SIZE) * TILE_SIZE
	y = p_y - ((x - p_x) * tan(angle))
*/

// vertical intersec steps
/*
	step_x = adjacent = TILE_SIZE
	step_y = opposite * tan(angle)
*/
double	v_interse_distance(t_cub *cub, double ray_angle)
{
	double		start_x;
	double		start_y;
	double		step_x;
	double		step_y;
	double		d;

	start_x = floor(cub->p->x_pixel / TILE_SIZE) * TILE_SIZE;
	cub->ray->for_norm = 0;
	adjust_intersec(cub->ray, 0, &start_x, NULL);
	start_y = cub->p->y_pixel
		+ ((start_x - cub->p->x_pixel) * tan(ray_angle));
	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(ray_angle);
	adjust_intersec(cub->ray, 1, &step_x, &step_y);
	while (start_x >= 0 && start_y >= 0)
	{
		if ((!cub->ray->facing_l_r && is_wall(cub, start_y, start_x - 1))
			|| is_wall(cub, start_y, start_x))
			break ;
		start_y += step_y;
		start_x += step_x;
	}
	d = sqrt(pow(start_x - cub->p->x_pixel, 2)
			+ pow(start_y - cub->p->y_pixel, 2));
	return (cub->ray->v_x = start_x, cub->ray->v_y = start_y, d);
}

void	cast_rays(t_cub *cub, double h_d, double v_d, int col)
{
	cub->ray->ray_angle = cub->p->angle - (cub->p->fov_rd / 2);
	(1) && (get_angle_facing(cub->ray), col = -1);
	while (++col < N_RAYS)
	{
		h_d = h_intersec_distance(cub, map_angle(cub->ray->ray_angle));
		v_d = v_interse_distance(cub, map_angle(cub->ray->ray_angle));
		if (v_d <= h_d)
		{
			(1) && (cub->ray->f = 0, cub->ray->distance_to_wall = v_d);
			cub->ray->tex_offset = (cub->ray->v_y / TILE_SIZE)
				- ((int)(cub->ray->v_y / TILE_SIZE));
		}
		else
		{
			(1) && (cub->ray->f = 1, cub->ray->distance_to_wall = h_d);
			cub->ray->tex_offset = (cub->ray->h_x / TILE_SIZE)
				- ((int)(cub->ray->h_x / TILE_SIZE));
		}
		render_obstacles(cub, col);
		cub->ray->ray_angle = map_angle(cub->ray->ray_angle
				+ cub->p->fov_rd / S_W);
		get_angle_facing(cub->ray);
	}
}
