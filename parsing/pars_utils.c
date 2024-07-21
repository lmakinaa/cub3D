/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 04:29:03 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/21 04:43:40 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			i++;
		else
			return (1);
	}
	return (0);
}

void	get_path(char **path, char *line)
{
	int		i;
	char	*trimed;

	i = 2;
	trimed = ft_strtrim(line + i, " \t\n\v\f\r");
	if (!trimed || ft_strlen(trimed) > 1024)
		*path = NULL;
	else
		*path = trimed;
}

bool	range_checker(int *nbrs, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		if (nbrs[i] > 255 || nbrs[i] < 0)
			exit_on_error("Error : color range invalid !\n", 30);
		i++;
	}
	return (true);
}

void	get_colors(int **color, char *line, int i, int flag)
{
	int		start;
	char	**array;
	int		*nbr;

	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
		i++;
	start = i;
	while (line[i])
	{
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == ',' && ft_isdigit(line[i - 1]))
			flag++;
		else if (flag != 2 || check(&line[i]))
			return ;
		(1) && (line[i]) && (i++);
	}
	if (++flag == 3)
	{
		array = ft_split(NULL, line + start, ',');
		nbr = heap_control(M_ALLOC, sizeof(int) * 3, 0, 1);
		while (flag--)
			nbr[2 - flag] = atoi(array[2 - flag]);
		(1) && (range_checker(nbr, sizeof(nbr) / 4)) && (*color = nbr);
	}
}

bool	get_params(char *line, t_map *map_data)
{
	if (!ft_strncmp(line, "NO ", 3) && !map_data->no)
		return (get_path(&map_data->no, line), true);
	else if (!ft_strncmp(line, "SO ", 3) && !map_data->so)
		return (get_path(&map_data->so, line), true);
	else if (!ft_strncmp(line, "WE ", 3) && !map_data->we)
		return (get_path(&map_data->we, line), true);
	else if (!ft_strncmp(line, "EA ", 3) && !map_data->ea)
		return (get_path(&map_data->ea, line), true);
	else if (!ft_strncmp(line, "F ", 2) && !map_data->floor)
		return (get_colors(&(map_data->floor), line, 1, 0), true);
	else if (!ft_strncmp(line, "C ", 2) && !map_data->ceil)
		return (get_colors(&(map_data->ceil), line, 1, 0), true);
	else if (*line == '\n')
		return (true);
	return (false);
}
