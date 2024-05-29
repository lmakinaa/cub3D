/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/29 18:58:57 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_texture(t_cub *cub, int x, int y)
{
	int		p_x;
	int		p_y;
	float	scale_factor;
	
	p_x = x % TILE_SIZE;
	p_y = y % TILE_SIZE;
	//printf("%d--%d//%d--%d\n", y, p_y, x, p_x);
	//sleep(2);
    scale_factor = (float)TILE_SIZE / cub->data->texture->width;
    p_x = (int)(p_x * scale_factor);
    scale_factor = (float)TILE_SIZE / cub->data->texture->height;
    p_y = (int)(p_y * scale_factor);
	mlx_put_pixel(cub->img, x, y, get_texture_pixel(cub->data->texture, p_x, p_y));
}

void	put_sky_n_floor(t_cub *cub, int s_y, int e_y, int col)
{
	int	i;

	i = 0;
	while (i < s_y)
		mlx_put_pixel(cub->img, col, i++, 0xF5F5F5FF);
	i = S_H;
	while (i > e_y)
		mlx_put_pixel(cub->img, col, i--, 0xF5F005FF);
}

void	put_wall(t_cub *cub, int s_y, int e_y, int col)
{
	while (s_y < e_y)
		//mlx_put_pixel(cub->img, col, s_y++, get_rgba(255, 255, 0, 100));
		put_texture(cub, col, s_y++);
}

// distance to projection plane = (S_W / 2) / tan(FOV / 2)
// projection wall height = (TILE_SIZE / ray distance) * distance to proj plane
void	render_obstacles(t_cub *cub, int col)
{
	double	proj_plane_dist;
	double	wall_height;

	proj_plane_dist = (S_W / 2) / tan(cub->p->fov_rd / 2);
	cub->ray->distance_to_wall *= cos((cub->ray->ray_angle - cub->p->angle));
	wall_height = (TILE_SIZE / cub->ray->distance_to_wall) * proj_plane_dist;
	double	start_p = (S_H / 2) - (wall_height / 2);
	if (start_p < 0)
		start_p = 0;
	double	end_p = (S_H / 2) + (wall_height / 2);
	if (end_p > S_H)
		end_p = S_H;
	put_wall(cub, start_p, end_p, col);
	put_sky_n_floor(cub, start_p, end_p, col);
}
