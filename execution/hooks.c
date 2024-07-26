/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:11:48 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/26 15:34:57 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit(int exit_status, t_cub *cub, char *error)
{
	if (exit_status)
		write(2, error, ft_strlen(error));
	clean_textures(cub);
	mlx_terminate(cub->mlx_p);
	heap_control(M_CLEAN, 0, 0, 0);
	exit(exit_status);
}

void	arrows_act(t_cub *cub, int d, int p)
{
	if (!d)
		return ;
	if (p == 1)
	{
		if (d == 'R' || d == 'W' || d == 'D')
			(p = 1);
		else if (d == 'L' || d == 'S' || d == 'A')
			(p = -1);
	}
	if (d == 'L' || d == 'R')
		cub->p->rot = p;
	else if (d == 'A' || d == 'D')
		cub->p->l_r = p;
	else if (d == 'W' || d == 'S')
		cub->p->u_d = p;
}

void	arrows_handle(mlx_key_data_t *k, t_cub *cub)
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
	else if (k->key == MLX_KEY_W)
		direction = 'W';
	else if (k->key == MLX_KEY_S)
		direction = 'S';
	else if (k->key == MLX_KEY_A)
		direction = 'A';
	else if (k->key == MLX_KEY_D)
		direction = 'D';
	arrows_act(cub, direction, press);
}

void	key_hooks(mlx_key_data_t k, void *m)
{
	t_cub	*cub;

	cub = m;
	if (k.key == MLX_KEY_ESCAPE)
	{
		clean_exit(0, cub, NULL);
	}
	arrows_handle(&k, cub);
}
