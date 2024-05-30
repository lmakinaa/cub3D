/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/30 11:28:21 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	put_wall(t_cub *cub, int s_y, int e_y, int col, double wall_height)
{
	float texture_offset_x = cub->ray->current_tex * cub->data->texture->width;
	int wall_start = s_y;
	while (s_y < e_y)
	{
		float texture_offset_y = (((float)s_y - (float)wall_start)
				/ (float)wall_height) * cub->data->texture->height;
		if (s_y >= 0 && s_y < S_H)
			mlx_put_pixel(cub->img, col, (int)s_y,
				get_texture_pixel(cub->data->texture, texture_offset_x, texture_offset_y));
		s_y += 1;
	}
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
	put_wall(cub, start_p, end_p, col, wall_height);
	put_sky_n_floor(cub, start_p, end_p, col);
}
