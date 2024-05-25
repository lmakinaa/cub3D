/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:11:48 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/23 23:12:07 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_position_valid(t_data *data, char direction)
{
	if (direction == 'L')
	{
		if (data->map2d[data->p_y][data->p_x - 1] == '1')
			return (0);
	}
	else if (direction == 'R')
	{
		if (data->map2d[data->p_y][data->p_x + 1] == '1')
			return (0);
	}
	else if (direction == 'D')
	{
		if (data->map2d[data->p_y + 1][data->p_x] == '1')
			return (0);
	}
	else if (direction == 'U')
	{
		if (data->map2d[data->p_y - 1][data->p_x] == '1')
			return (0);
	}
	return (1);
}

void	arrows_act(t_cub *cub, int d, int p)
{
	if (!d)
		return ;
	if (p == 1)
	{
		if (d == 'R' || d == 'U')
			(is_position_valid(cub->data, d)) && (p = 1);
		else if (d == 'L' || d == 'D')
			(is_position_valid(cub->data, d)) && (p = -1);
	}
	if (d == 'L' || d == 'R')
		cub->p->l_r = p;
	else if (d == 'U' || d == 'D')
		cub->p->u_d = p;
}

void	arrows_handle(mlx_key_data_t *k, t_cub *cub, void (*f)(t_cub *cub, int d, int p))
{
	int	press;
	int	direction;

	press = 1;
	if (k->action == MLX_RELEASE)
		press = 0;

	direction = 0;
	if (k->key == MLX_KEY_RIGHT)
		direction = 'R';
	else if (k->key == MLX_KEY_LEFT)
		direction = 'L';
	else if (k->key == MLX_KEY_UP)
		direction = 'U';
	else if (k->key == MLX_KEY_DOWN)
		direction = 'D';
	f(cub, direction, press);
}

void	key_hooks(mlx_key_data_t k, void *m)
{
	t_cub	*cub;

	cub = m;
	arrows_handle(&k, cub, arrows_act);
	
}
