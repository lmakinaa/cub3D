/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:05:18 by ijaija            #+#    #+#             */
/*   Updated: 2024/08/06 14:35:01 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINI_TILE_SIZE)
	{
		j = -1;
		while (++j < MINI_TILE_SIZE)
			mlx_put_pixel(cub->minimap_img, x + i, y + j, color);
	}
}

void	draw_mini_player(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MINI_TILE_SIZE / 4)
	{
		j = -1;
		while (++j < MINI_TILE_SIZE / 4)
			mlx_put_pixel(cub->minimap_img, x + i, y + j, color);
	}
}

void	draw_minimap(t_cub *cub)
{
	int		x;
	int		y;
	char	**map;
	int		color;

	map = cub->data->map_2d;
	y = -1;
	while (++y < cub->data->h_map)
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0' || ft_strchr("NSWE", map[y][x]))
				color = C_TRANSPARENT;
			else
				color = 0x000000FF;
			draw_tile(cub, x * MINI_TILE_SIZE, y * MINI_TILE_SIZE, color);
		}
	}
	draw_mini_player(cub, 0.2 * cub->p->x_pixel, 0.2 * cub->p->y_pixel, 0xFF0F00FF);
}
