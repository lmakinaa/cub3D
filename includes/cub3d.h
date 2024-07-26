/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:31:35 by ijaija            #+#    #+#             */
/*   Updated: 2024/07/26 15:35:25 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./heap_control.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "MLX42.h"
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
# define TILE_SIZE 32
# define R_S 2
# define PLAYER_SPEED 2
# define N_RAYS 1000
# define MINI_TILE_SIZE 6.4

typedef struct s_player
{
	int		x_pixel;
	int		y_pixel;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}	t_player;

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
	int		f;
	int		for_norm;
	float	wall_height;
	float	tex_offset;
}	t_ray;

typedef struct s_data
{
	char			**map_2d;
	int				p_x;
	int				p_y;
	int				w_map;
	int				h_map;
	mlx_image_t		*textures[4];
	char			**texture_paths;
	int				sky_c;
	int				floor_c;
	struct s_cub	*cub;
}	t_data;

typedef struct s_cub
{
	mlx_image_t		*img;
	mlx_image_t		*minimap_img;
	mlx_t			*mlx_p;
	t_ray			*ray;
	t_data			*data;
	t_player		*p;
	struct s_map	*parsing;
}	t_cub;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*textures[4];
	int		*floor;
	int		*ceil;
	char	**map;
	char	player;
	int		p_x;
	int		p_y;
	int		height;
	int		width;
}	t_map;

void		cast_rays(t_cub *cub, double h_d, double v_d, int col);
void		get_colors(int **color, char *line, int i, int flag);
void		draw_minimap(t_cub *cub);
t_data		*init_data(t_map *map_data);
void		init_the_player(t_cub *cub);
void		key_hooks(mlx_key_data_t k, void *m);
void		game_loop(void *m);
int			get_rgba(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a);
void		update_vars(t_cub *cub);
double		map_angle(double angle);
uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y);
void		render_obstacles(t_cub *cub, int col);
void		put_sky_n_floor(t_cub *cub);
int			is_wall(t_cub *cub, double start_y, double start_x);
void		clean_exit(int exit_status, t_cub *cub, char *error);
void		clean_textures(t_cub *cub);
void		get_angle_facing(t_ray *ray);
void		adjust_p_angle(t_cub *cub);

char		*ft_strtrim(char *str, char *set);
int			ft_isdigit(int c);
bool		range_checker(int *nbrs, int size);
char		*get_next_line(int fd);
void		*ft_memcpy(void *dst, const void *src, size_t len);
void		*ft_memset(void *str, int c, size_t len);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
char		**ft_split(int *height, char *original, char c);
char		*ft_strdup(const char *str);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strlen(const char *s);
char		*ft_substr(const char *str, int start, int len);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t len);
void		*ft_memset(void *str, int c, size_t len);
char		*ft_strchr(const char *str, int c);
int			vr(void);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
t_map		*is_valid_map(char **argv, char *line, char	*one_line_map,
				int flag);
int			check(char *line);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		get_path(char **path, char *line);
bool		range_checker(int *nbrs, int size);
void		get_colors(int **color, char *line, int i, int flag);
bool		get_params(char *line, t_map *map_data);

#endif
