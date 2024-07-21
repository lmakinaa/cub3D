/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:43:23 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/21 03:07:46 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	vr(void)
{
	return (0);
}

int	get_rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// normalizing angle
double	map_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	else if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y)
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	*offset;

	offset = &texture->pixels[((y * texture->width) + x) * 4];
	r = offset[0];
	g = offset[1];
	b = offset[2];
	a = offset[3];
	return (get_rgba(r, g, b, a));
}

void	put_sky_n_floor(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < S_H / 2)
	{
		j = -1;
		while (++j < S_W)
			mlx_put_pixel(cub->img, j, i, cub->data->sky_c);
	}
	while (++i < S_H)
	{
		j = -1;
		while (++j < S_W)
			mlx_put_pixel(cub->img, j, i, cub->data->floor_c);
	}
}
