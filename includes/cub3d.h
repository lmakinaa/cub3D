/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:26:59 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/30 21:33:48 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./heap_control.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "MLX42.h"
# include <string.h>
# include <stdio.h>

# define ASSET1 "/Users/ijaija/new-cub/textures/wall.png"

# define MAIN 0
# define MINIMAP 1

# define C_TRANSPARENT 0xFF000000

# define S_W 1900
# define S_H 1000
# define FOV 80
# define TILE_SIZE 64
# define ROTATION_SPEED 3 * M_PI / 180
# define PLAYER_SPEED 2
# define N_RAYS S_W / 1

# define MINIMAP_SCALE 0.2
# define MINIMAP_W S_W * MINIMAP_SCALE
# define MINIMAP_H S_H * MINIMAP_SCALE
# define MINI_TILE_SIZE TILE_SIZE * MINIMAP_SCALE

typedef struct s_player
{
	int		x_pixel;
	int		y_pixel;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}		t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance_to_wall;
	float	n_rays;
	int		facing_u_d;
	int		facing_l_r;
	double	v_x;
	double	v_y;
	double	h_x;
	double	h_y;
	float	tex_offset;
}		t_ray;

typedef struct s_data
{
	char			**map2d;
	int				p_x;
	int				p_y;
	int				w_map;
	int				h_map;
	mlx_image_t 	*texture;
	struct s_cub	*cub;
}		t_data;

typedef struct s_cub
{
	mlx_image_t		*img;
	mlx_image_t		*minimap_img;
	mlx_t			*mlx_p;
	t_ray			*ray;
	t_data			*data;
	t_player		*p;
} 		t_cub;

void 			cast_rays(t_cub *cub, int x, int y);
void			draw_minimap(t_cub *cub);
t_data			*init_data(void);
void			init_the_player(t_cub *cub);
void			key_hooks(mlx_key_data_t k, void *m);
void 			game_loop(void *m);
void 			draw_line(t_cub *cub, int beginX, int beginY, int endX, int endY, int color);
int 			get_rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void			update_vars(t_cub *cub);
double			map_angle(double angle);
uint32_t		get_texture_pixel(mlx_image_t *texture, int x, int y);
void			render_obstacles(t_cub *cub, int col);
void			put_sky_n_floor(t_cub *cub);

#endif