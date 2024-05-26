/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:17:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/26 15:26:47 by ijaija           ###   ########.fr       */
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
		(!cub->ray->facing_u_d) && (start_y--);
		if (is_wall(cub, start_y, start_x))
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
		(!cub->ray->facing_l_r) && (start_x--);
		if (is_wall(cub, start_y, start_x))
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
		
		draw_line(cub, x, y,
		ray_x,
		ray_y,
		get_rgba(0, 0, 255, 255));
		cub->ray->ray_angle += cub->p->fov_rd / S_W;
		get_angle_facing(cub->ray);
	}
}


//int unit_circle(float angle, char c) // check the unit circle
//{
//	if (c == 'x')
//	{
//		if (angle > 0 && angle < M_PI)
//		return (1);
//	}
//	else if (c == 'y')
//	{
//		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
//		return (1);
//	}
//	return (0);
//}

//int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
//{
//	if (is_horizon)
//	{
//		if (angle > 0 && angle < M_PI)
//		{
//			*inter += TILE_SIZE;
//			return (-1);
//		}
//		*step *= -1;
//	}
//	else
//	{
//		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
//		{
//			*inter += TILE_SIZE;
//			return (-1);
//		}
//		*step *= -1;
//	}
//	return (1);
//}

//int wall_hit(float x, float y, t_mlx *mlx) // check the wall hit
//{
//	int  x_m;
//	int  y_m;

//	if (x < 0 || y < 0)
//		return (0);
//	x_m = floor (x / TILE_SIZE); // get the x position in the map
//	y_m = floor (y / TILE_SIZE); // get the y position in the map
//	if ((y_m >= mlx->dt->h_map || x_m >= mlx->dt->w_map))
//		return (0);
//	if (mlx->dt->map2d[y_m] && x_m <= (int)strlen(mlx->dt->map2d[y_m]))
//		if (mlx->dt->map2d[y_m][x_m] == '1')
//			return (0);
//	return (1);
//}

//float get_h_inter(t_mlx *mlx, float angl) // get the horizontal intersection
//{
//	float h_x;
//	float h_y;
//	float x_step;
//	float y_step;
//	int  pixel;

//	y_step = TILE_SIZE;
//	x_step = TILE_SIZE / tan(angl);
//	h_y = floor(mlx->ply->plyr_y / TILE_SIZE) * TILE_SIZE;
//	pixel = inter_check(angl, &h_y, &y_step, 1);
//	h_x = mlx->ply->plyr_x + (h_y - mlx->ply->plyr_y) / tan(angl);
//	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
//		x_step *= -1;
//	while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
//	{
//		h_x += x_step;
//		h_y += y_step;
//	}
//	return (sqrt(pow(h_x - mlx->ply->plyr_x, 2) + pow(h_y - mlx->ply->plyr_y, 2))); // get the distance
//}

//float get_v_inter(t_mlx *mlx, float angl) // get the vertical intersection
//{
//	float v_x;
//	float v_y;
//	float x_step;
//	float y_step;
//	int  pixel;

//	x_step = TILE_SIZE; 
//	y_step = TILE_SIZE * tan(angl);
//	v_x = floor(mlx->ply->plyr_x / TILE_SIZE) * TILE_SIZE;
//	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
//	v_y = mlx->ply->plyr_y + (v_x - mlx->ply->plyr_x) * tan(angl);
//	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
//		y_step *= -1;
//	while (wall_hit(v_x - pixel, v_y, mlx)) // check the wall hit whit the pixel value
//	{
//		v_x += x_step;
//		v_y += y_step;
//	}
//	return (sqrt(pow(v_x - mlx->ply->plyr_x, 2) + pow(v_y - mlx->ply->plyr_y, 2))); // get the distance
//}

//void cast_rays(t_mlx *mlx) // cast the rays
//{
//	double h_inter;
//	double v_inter;
//	int  ray;

//	ray = 0;
//	mlx->ray->ray_ngl = mlx->ply->angle - (mlx->ply->fov_rd / 2); // the start angle
//	while (ray < S_W) // loop for the rays
//	{
//		mlx->ray->flag = 0; // flag for the wall
//		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
//		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
//		if (v_inter <= h_inter) // check the distance
//			mlx->ray->distance = v_inter; // get the distance
//		else
//		{
//			mlx->ray->distance = h_inter; // get the distance
//			mlx->ray->flag = 1; // flag for the wall
//		}
//		render_wall(mlx, ray); // render the wall
//		ray++; // next ray
//		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
//	}
//}