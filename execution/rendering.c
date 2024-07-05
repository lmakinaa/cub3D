/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/05 09:45:02 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall(t_cub *cub, int s_y, int e_y, int col, float wall_height)
{
	int	tex_offset_y;
	int tex_offset_x = cub->ray->tex_offset * cub->data->texture->width;
	tex_offset_x -= (tex_offset_x == cub->data->texture->width);
	int wall_start = s_y;
	while (s_y < e_y)
	{
		tex_offset_y = (((float)s_y - (float)wall_start)
				/ (float) wall_height) * cub->data->texture->height;
		tex_offset_y -= (tex_offset_y == cub->data->texture->height);
		if (s_y < 0 || s_y > S_H)
		{
			s_y++;
			continue ;
		}
		mlx_put_pixel(cub->img, col, s_y,
			get_texture_pixel(cub->data->texture, tex_offset_x, tex_offset_y));
		s_y++;
	}
}

// distance to projection plane = (S_W / 2) / tan(FOV / 2)
// projection wall height = (TILE_SIZE / ray distance) * distance to proj plane
void	render_obstacles(t_cub *cub, int col)
{
	double	proj_plane_dist;
	double	wall_height;

	proj_plane_dist = (S_W / 2) / tan(cub->p->fov_rd / 2);
	printf("%f\n", cub->ray->distance_to_wall);
	cub->ray->distance_to_wall *= cos((cub->ray->ray_angle - cub->p->angle));
	// cub->ray->distance_to_wall have a problem
	// it reach 0 and when calculating wall_height it result to inf
	wall_height = (TILE_SIZE / cub->ray->distance_to_wall) * proj_plane_dist;
	double	start_p = (S_H / 2) - (wall_height / 2);
	double	end_p = (S_H / 2) + (wall_height / 2);
	if (end_p > S_H)
		end_p = S_H;
	put_wall(cub, start_p, end_p, col, wall_height);
}
