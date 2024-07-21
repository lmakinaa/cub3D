/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 02:20:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*get_what_texture(t_cub *cub)
{
	if (!cub->ray->f)
	{
		if (cub->ray->ray_angle > M_PI / 2 && cub->ray->ray_angle < 3 * (M_PI / 2))
			return (cub->data->textures[2]); // west wall
		else
			return (cub->data->textures[3]); // east wall
	}
	else
	{
		if (cub->ray->ray_angle > 0 && cub->ray->ray_angle < M_PI)
			return (cub->data->textures[1]); // south wall
		else
			return (cub->data->textures[0]); // north wall
	}
}

void	put_wall(t_cub *cub, int s_y, int e_y, int col, float wall_height)
{
	mlx_image_t	*texture;

	texture = get_what_texture(cub);
	int	tex_offset_y;
	int tex_offset_x = cub->ray->tex_offset * texture->width;
	tex_offset_x -= (tex_offset_x == texture->width);
	int wall_start = s_y;
	if (s_y < 0)
		s_y = 0;
	while (s_y < e_y)
	{
		tex_offset_y = (((float)s_y - (float)wall_start)
				/ (float) wall_height) * texture->height;
		tex_offset_y -= (tex_offset_y == texture->height);
		mlx_put_pixel(cub->img, col, s_y,
			get_texture_pixel(texture, tex_offset_x, tex_offset_y));
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
	if (!cub->ray->distance_to_wall)
		cub->ray->distance_to_wall = 0.1;
	cub->ray->distance_to_wall *= cos((cub->ray->ray_angle - cub->p->angle));
	// printf("%d\n", cub->ray->distance_to_wall);
	if (cub->ray->distance_to_wall == 0 )
		{return ;}
	else
	{
	wall_height = (TILE_SIZE / cub->ray->distance_to_wall) * proj_plane_dist;
	double	start_p = (S_H / 2) - (wall_height / 2);
	double	end_p = (S_H / 2) + (wall_height / 2);
	if (end_p > S_H)
		end_p = S_H;
	put_wall(cub, start_p, end_p, col, wall_height);
	}
		
	// cub->ray->distance_to_wall have a problem
	// it reach 0 and when calculating wall_height it result to inf
}
