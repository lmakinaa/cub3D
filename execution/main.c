/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:09:29 by ijaija            #+#    #+#             */
/*   Updated: 2024/08/06 14:35:34 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_delete_image(cub->mlx_p, cub->data->textures[i]);
}

void	load_textures(t_data *d)
{
	mlx_texture_t	*tmp;
	int				i;

	i = -1;
	while (++i < 4)
	{
		tmp = mlx_load_png(d->texture_paths[i]);
		if (!tmp)
			clean_exit(1, d->cub, "mlx_load_png() failed\n");
		d->textures[i] = mlx_texture_to_image(d->cub->mlx_p, tmp);
		if (!d->textures[i])
			clean_exit(1, d->cub, "mlx_texture_to_image() failed\n");
		mlx_delete_texture(tmp);
	}
}

void	game_loop(void *m)
{
	t_cub	*cub;

	cub = m;
	update_vars(cub);
	put_sky_n_floor(cub);
	cast_rays(cub, 0, 0, -1);
	draw_minimap(cub);
}

void	start_the_game(t_data *data)
{
	t_cub			*cub;

	cub = data->cub;
	cub->data = data;
	cub->p = heap_control(M_ALLOC, sizeof(t_player), 0, 1);
	adjust_p_angle(cub);
	cub->ray = heap_control(M_ALLOC, sizeof(t_ray), 0, 1);
	cub->mlx_p = mlx_init(S_W, S_H, "cub3d", true);
	if (!cub->mlx_p)
		exit_on_error("mlx_init() failed\n", 18);
	cub->img = mlx_new_image(cub->mlx_p, S_W, S_H);
	if (!cub->img || (mlx_image_to_window(cub->mlx_p, cub->img, 0, 0) < 0))
		clean_exit(1, cub, "mlx_new_image() failed\n");
	cub->minimap_img = mlx_new_image(cub->mlx_p, cub->data->w_map * MINI_TILE_SIZE, cub->data->h_map * MINI_TILE_SIZE);
	if (!cub->minimap_img || (mlx_image_to_window(cub->mlx_p, cub->minimap_img, 5, 5) < 0))
		clean_exit(1, cub, "mlx_new_image() failed\n");
	load_textures(data);
	init_the_player(cub);
	mlx_key_hook(cub->mlx_p, key_hooks, cub);
	mlx_loop_hook(cub->mlx_p, game_loop, cub);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_map	*map_data;

	if (argc != 2)
		return (exit_on_error("Error: invalid number of arguments\n", 35), 0);
	map_data = is_valid_map(argv, NULL, NULL, 0);
	map_data->textures[0] = map_data->no;
	map_data->textures[1] = map_data->so;
	map_data->textures[2] = map_data->we;
	map_data->textures[3] = map_data->ea;
	data = init_data(map_data);
	data->texture_paths = map_data->textures;
	start_the_game(data);
	mlx_loop(data->cub->mlx_p);
	mlx_terminate(data->cub->mlx_p);
	heap_control(M_CLEAN, 0, 0, 0);
	return (0);
}
