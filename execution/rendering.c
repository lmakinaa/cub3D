/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 04:18:25 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*get_what_texture(t_cub *cub)
{
	if (!cub->ray->f)
	{
		if (cub->ray->ray_angle > M_PI / 2
			&& cub->ray->ray_angle < 3 * (M_PI / 2))
			return (cub->data->textures[2]);
		else
			return (cub->data->textures[3]);
	}
	else
	{
		if (cub->ray->ray_angle > 0 && cub->ray->ray_angle < M_PI)
			return (cub->data->textures[1]);
		else
			return (cub->data->textures[0]);
	}
}

void	put_wall(t_cub *cub, int s_y, int e_y, int col)
{
	mlx_image_t	*texture;
	int			tex_offset_y;
	int			tex_offset_x;
	int			wall_start;

	texture = get_what_texture(cub);
	tex_offset_x = cub->ray->tex_offset * texture->width;
	tex_offset_x -= ((uint32_t) tex_offset_x == texture->width);
	wall_start = s_y;
	if (s_y < 0)
		s_y = 0;
	while (s_y < e_y)
	{
		tex_offset_y = (((float)s_y - (float)wall_start)
				/ (float)cub->ray->wall_height) * texture->height;
		tex_offset_y -= ((uint32_t) tex_offset_y == texture->height);
		mlx_put_pixel(cub->img, col, s_y,
			get_texture_pixel(texture, tex_offset_x, tex_offset_y));
		s_y++;
	}
}

void	render_obstacles(t_cub *cub, int col)
{
	double	proj_plane_dist;
	double	start_p;
	double	end_p;

	proj_plane_dist = (S_W / 2) / tan(cub->p->fov_rd / 2);
	if (!cub->ray->distance_to_wall)
		cub->ray->distance_to_wall = 0.1;
	cub->ray->distance_to_wall *= cos((cub->ray->ray_angle - cub->p->angle));
	if (cub->ray->distance_to_wall == 0)
		return ;
	else
	{
		cub->ray->wall_height = (TILE_SIZE / cub->ray->distance_to_wall)
			* proj_plane_dist;
		start_p = (S_H / 2) - (cub->ray->wall_height / 2);
		end_p = (S_H / 2) + (cub->ray->wall_height / 2);
		if (end_p > S_H)
			end_p = S_H;
		put_wall(cub, start_p, end_p, col);
	}
}
