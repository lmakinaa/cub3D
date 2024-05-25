/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:43:23 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/24 02:06:21 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	vr(void)
{
	return (0);
}

// hadi 3ir katpushi limg flwindow
void	display_img(t_cub *mlx, int what_img)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	if (what_img == MAIN)
		(1) && (x = 0, y = 0, img = mlx->img, vr());
	else if (what_img == MINIMAP)
		(1) && (x = 0, y = S_H - MINIMAP_H, img = mlx->minimap_img, vr());
	mlx_image_to_window(mlx->mlx_p, img, 0, 0);
}

// hadi katcree image w katinitialisiha
void	new_img(t_cub *cub, int what_img)
{
	int			h;
	int			w;

	if (what_img == MAIN)
	{
		(1) && (h = S_H, w = S_W);
		mlx_delete_image(cub->mlx_p, cub->img);
		cub->img = mlx_new_image(cub->mlx_p, w, h);
	}
	else if (what_img == MINIMAP)
	{
		(1) && (h = MINIMAP_H, w = MINIMAP_W);
		mlx_delete_image(cub->mlx_p, cub->minimap_img);
		cub->minimap_img = mlx_new_image(cub->mlx_p, w, h);
	}
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

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

double	map_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	else if (angle > 0)
		angle -= (2 * M_PI);
	return (angle);
}
