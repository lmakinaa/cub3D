/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:17:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/28 18:56:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	get_angle_facing(t_ray *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->facing_u_d = 1;
	else
		ray->facing_u_d = 0;
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI)
		ray->facing_l_r = 1;
	else
		ray->facing_l_r = 0;
}

void	adjust_intersec(t_ray *ray, int step, double *n_x, double *n_y, int h)
{
	if (h)
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

	if (start_y < 0 || start_x < 0 || start_x > S_W || start_y > S_H)
		return (1);
	y = floor(start_y / TILE_SIZE);
	x = floor(start_x / TILE_SIZE);
	if (y >= cub->data->h_map || x >= cub->data->w_map)
		return (1);
	if (cub->data->map2d[y][x] == '1')
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
	adjust_intersec(cub->ray, 0, NULL, &start_y, 1);
	start_x = cub->p->x_pixel
		+ ((start_y - cub->p->y_pixel) / tan(ray_angle));
	step_y = TILE_SIZE;
	step_x = TILE_SIZE / tan(ray_angle);
	adjust_intersec(cub->ray, 1, &step_x, &step_y, 1);
	while (start_x >= 0 && start_x <= S_W && start_y >= 0 && start_y <= S_H)
	{
		if ((!cub->ray->facing_u_d && is_wall(cub, start_y - 1, start_x))
			|| is_wall(cub, start_y, start_x))
			break ;
		start_y += step_y;
		start_x += step_x;
	}
	d = sqrt(pow(start_x - cub->p->x_pixel, 2)
		+ pow(start_y - cub->p->y_pixel, 2));
	cub->ray->h_x = start_x;
	cub->ray->h_y = start_y;
	return (d);
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
	adjust_intersec(cub->ray, 0, &start_x, NULL, 0);
	start_y = cub->p->y_pixel
		+ ((start_x - cub->p->x_pixel) * tan(ray_angle));
	step_x = TILE_SIZE;
	step_y = TILE_SIZE * tan(ray_angle);
	adjust_intersec(cub->ray, 1, &step_x, &step_y, 0);
	while (start_x >= 0 && start_x <= S_W && start_y >= 0 && start_y <= S_H)
	{
		if ((!cub->ray->facing_l_r && is_wall(cub, start_y, start_x - 1))
			|| is_wall(cub, start_y, start_x))
			break ;
		start_y += step_y;
		start_x += step_x;
	}
	d = sqrt(pow(start_x - cub->p->x_pixel, 2)
		+ pow(start_y - cub->p->y_pixel, 2));
	cub->ray->v_x = start_x;
	cub->ray->v_y = start_y;
	return (d);
}

//void draw_slice(t_cub *cub, int col, double ray_length)
//{
//    // Calculate the wall height
//    int wall_height = (int)(S_H / ray_length);

//    // Calculate the start and end positions for the wall slice
//    int start = (S_H / 2) - (wall_height / 2);
//    start = start < 0 ? 0 : start;
//    int end = (S_H / 2) + (wall_height / 2);
//    end = end > S_H ? S_H : end;

//    // Draw the ceiling, wall, and floor
//    for (int y = 0; y < S_H; y++)
//    {
//        if (y < start)
//        {
//            // Draw the ceiling
//            mlx_put_pixel(cub->img, col, y, get_rgba(255, 255, 255, 255)); // White color
//        }
//        else if (y >= start && y < end)
//        {
//            // Draw the wall
//            mlx_put_pixel(cub->img, col, y, get_texture_pixel(cub->data->texture, col, y)); // Blue color
//        }
//        else
//        {
//            // Draw the floor
//            mlx_put_pixel(cub->img, col, y, get_rgba(128, 128, 128, 255)); // Gray color
//        }
//    }
//}

void cast_rays(t_cub *cub, int x, int y)
{
	int	col;

	cub->ray->ray_angle = cub->p->angle - (cub->p->fov_rd / 2);
	get_angle_facing(cub->ray);
	col = -1;
	while (++col < N_RAYS)
	{
		double ray_x = 0;
        double ray_y = 0;
		double	h_d = h_intersec_distance(cub, map_angle(cub->ray->ray_angle));
		double	v_d = v_interse_distance(cub, map_angle(cub->ray->ray_angle));
		if (v_d <= h_d)
		{
			cub->ray->distance_to_wall = v_d;
			ray_x = cub->ray->v_x;
			ray_y = cub->ray->v_y;
		}
		else
		{
			cub->ray->distance_to_wall = h_d;
			ray_x = cub->ray->h_x;
			ray_y = cub->ray->h_y;
		}
		//draw_slice(cub, col, cub->ray->distance_to_wall);
		//draw_line(cub, x, y,
		//MINIMAP_SCALE * ray_x,
		//MINIMAP_SCALE * ray_y,
		//get_rgba(0, 0, 255, 255));
		render_wall(cub, col);
		cub->ray->ray_angle += cub->p->fov_rd / S_W;
		get_angle_facing(cub->ray);
	}
}
