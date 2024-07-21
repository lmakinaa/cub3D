/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:33:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/21 04:43:37 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_params(t_map *map_data)
{
	if (!map_data->no || !map_data->so || !map_data->we || \
		!map_data->ea || !map_data->floor || !map_data->ceil)
		return (false);
	return (true);
}

bool	check_borders(char **map, int i, int j)
{
	if (i - 1 < 0 || !ft_strchr("01NSEW", map[i - 1][j]))
		return (false);
	if (j - 1 < 0 || !ft_strchr("01NSEW", map[i][j - 1]))
		return (false);
	if (!map[i + 1] || !ft_strchr("01NSEW", map[i + 1][j]))
		return (false);
	if (!map[i][j + 1] || !ft_strchr("01NSEW", map[i][j + 1]))
		return (false);
	return (true);
}

bool	check_map(char **map, t_map *data, int i, int j)
{
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(" 01NSEW", map[i][j]))
				exit_on_error("Error: invalid map character\n", 30);
			if (ft_strchr("0NSEW", map[i][j]))
			{
				if (map[i][j] != '0' && data->player)
					exit_on_error("Error: multiple players\n", 24);
				else if (map[i][j] != '0')
				{
					data->player = map[i][j];
					data->p_x = i;
					data->p_y = j;
				}
				if (!check_borders(map, i, j))
					exit_on_error("Error: invalid map borders\n", 27);
			}
		}
	}
	(!data->player) && (exit_on_error("Error: no player\n", 17), vr());
	return (true);
}

static int	for_norminette(t_map *map_data, char *line, int fd)
{
	if (!check_params(map_data))
	{
		if (!get_params(line, map_data) && !close(fd))
			exit_on_error("Error: invalid map parameters\n", 30);
		return (1);
	}
	return (0);
}

t_map	*is_valid_map(char **argv, char *line, char	*one_line_map)
{
	t_map	*map_data;
	int		fd;
	char	*tmp;

	if (ft_strnstr(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) == NULL)
		exit_on_error("Error: invalid file extension\n", 30);
	(1) && (map_data = heap_control(1, sizeof(t_map), NULL, 1),
			map_data->width = 0, fd = open(argv[1], O_RDONLY));
	(fd < 0) && (exit_on_error("Error: open(2) failed\n", 22), vr());
	while (1)
	{
		(1) && (heap_control(M_DEL, 0, line, 0), line = get_next_line(fd));
		if (!line)
			break ;
		if (for_norminette(map_data, line, fd))
			continue ;
		if (ft_strlen(line) - 1 > map_data->width)
			map_data->width = ft_strlen(line) - 1;
		(1) && (tmp = one_line_map, one_line_map = ft_strjoin(tmp, line),
			heap_control(M_DEL, 0, tmp, 0), vr());
	}
	map_data->map = ft_split(&map_data->height, one_line_map, '\n');
	return (check_map(map_data->map, map_data, -1, -1), close(fd), map_data);
}
