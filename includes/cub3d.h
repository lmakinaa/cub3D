/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:26:59 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/20 13:45:42 by ijaija           ###   ########.fr       */
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
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define ASSET1 "./textures/wall.png"

# define MAIN 0
# define MINIMAP 1

# define C_TRANSPARENT 0xFF000000

# define S_W 1000
# define S_H 1000
# define FOV 65
# define TILE_SIZE (double)32
# define ROTATION_SPEED 2 * M_PI / 180
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
	char			**map_2d;
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

//------------------------------------------------------
typedef struct s_map
{
	char    *NO;
	char    *SO;
	char    *WE;
	char	*EA;
	int     *F;
	int     *C;
	char    **map;
	char 		player;
	int         p_x;
	int 		p_y;		
	int		height;
} t_map;

void 			cast_rays(t_cub *cub, int x, int y);
void			draw_minimap(t_cub *cub);
t_data			*init_data(t_map *map_data);
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
int				is_wall(t_cub *cub, double start_y, double start_x);

//------------------------------------------------------

char	*ft_strtrim(char *str, char *set);
int		ft_isdigit(int c);
bool	range_checker(int *nbrs, int size);
char	*get_next_line(int fd);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t len);
int     ft_atoi(const char *str);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
int     ft_isalpha(int c);
char	**ft_split(int *height, char *original, char c);
char    *ft_strdup(const char *str);
char    *ft_strjoin(const char *s1, const char *s2);
int     ft_strlen(const char *s);
char    *ft_substr(const char *str, int start, int len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
t_map	*is_valid_map(char **argv, char *line);
void	print_map_data(t_map *map_data);

#endif