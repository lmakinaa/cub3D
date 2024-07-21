/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:33:56 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/21 03:28:00 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void get_path(char **path, char *line)
{
	int i = 2;
	char *trimed;
	trimed = ft_strtrim(line + i, " \t\n\v\f\r");
	if(!trimed || ft_strlen(trimed) > 1024)
		*path = NULL;
	else
		*path = trimed;
}

//  F 220,100,0
bool range_checker(int *nbrs, int size)
{
	int i;

	i = 0;
	while(i <= size)
	{
		if(nbrs[i] > 255 || nbrs[i] < 0)
			exit_on_error("Error : color range invalid !\n", 30);
		i++;
	}
	return (true);
}
int check(char *line)
{
	int i = 0;
	while(line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13)  || line[i] == 32)
			i++;
		else
			return (1);
	}
	return (0);
}
void get_colors(int **color, char *line)
{
	int i = 1;
	int start;
	int flag = 0;
	char **array;
	while(line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
		i++;
	start = i;
	while(line[i])
	{
		while(ft_isdigit(line[i]))
			i++;
		if(line[i] == ',' && ft_isdigit(line[i - 1]))
			flag++;
		else if (flag != 2 || check(&line[i]))
			return ;
		if (line[i])
			i++;
	}
	if (++flag == 3)
	{
		array = ft_split(NULL, line + start, ',');
		int *nbr = heap_control(M_ALLOC, sizeof(int) * 3, 0, 1);
		while (flag--)
		{
			nbr[2 - flag] = atoi(array[2 - flag]);
		}
		if(range_checker(nbr, sizeof(nbr)/4))
			(*color) = nbr;
	}
}

bool	get_params(char *line, t_map *map_data)
{
	if(!ft_strncmp(line,"NO ",3) && !map_data->no)
		return(get_path(&map_data->no, line), true);
	else if(!ft_strncmp(line,"SO ",3) && !map_data->so)
		return(get_path(&map_data->so, line), true);
	else if(!ft_strncmp(line,"WE ",3) && !map_data->we)
		return(get_path(&map_data->we, line), true);
	else if(!ft_strncmp(line,"EA ",3) && !map_data->ea)
		return(get_path(&map_data->ea, line), true);
	else if(!ft_strncmp(line,"F ",2) && !map_data->floor)
		return(get_colors(&(map_data->floor), line), true);
	else if(!ft_strncmp(line,"C ",2) && !map_data->ceil)
		return(get_colors(&(map_data->ceil), line), true);
	else if (*line == '\n')
		return (true);
	return(false);
}
bool check_params(t_map *map_data)
{
	if (!map_data->no || !map_data->so || !map_data->we||\
		!map_data->ea || !map_data->floor || !map_data->ceil)
		return (false);
	return (true);
}
bool	check_borders(char **map,int i, int j)
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

bool check_map(char **map, t_map *data)
{
	int i;
	int j;

	i = -1;
	while(map[++i])
	{
		j = -1;
		while(map[i][++j])
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
				if(!check_borders(map, i, j))
					exit_on_error("Error: invalid map borders\n", 27);
			}
		}
	}
	(!data->player) && (exit_on_error("Error: no player\n", 17), vr());
	return (true);
}

t_map	*is_valid_map(char **argv, char *line)
{
	t_map	*map_data;
	int		fd;
	char	*tmp;
	char	*one_line_map = NULL;

    if (ft_strnstr(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) == NULL)
		exit_on_error("Error: invalid file extension\n", 30);
	map_data = heap_control(1, sizeof(t_map), NULL, 1);
	map_data->width = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_on_error("Error: open(2) failed\n", 22);
	while (1)
	{
		heap_control(M_DEL, 0, line, 0);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_params(map_data))
		{
			if(!get_params(line, map_data))
				exit_on_error("Error: invalid map parameters\n", 30);
			continue ;
		}
		if (ft_strlen(line) - 1 > map_data->width)
			map_data->width = ft_strlen(line) - 1;
		(1) && (tmp = one_line_map, one_line_map = ft_strjoin(tmp, line),
			heap_control(M_DEL, 0, tmp, 0), vr());
	}
	map_data->map = ft_split(&map_data->height, one_line_map, '\n');
	map_data->player = 0;
	return (check_map(map_data->map, map_data), close(fd), map_data);
}
