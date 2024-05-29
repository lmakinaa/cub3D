/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:43:23 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/29 17:07:41 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	vr(void)
{
	return (0);
}

void	draw_line(t_cub *cub, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(cub->minimap_img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

int get_rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
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

int	get_texture_pixel(mlx_image_t *texture, int x, int y)
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
