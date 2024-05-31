/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:01:07 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/21 22:02:30 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	allocation(char **buffer)
{
	char	*ptr;
	int		i;

	if (!(*buffer))
	{
		*buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!(*buffer))
			return (0);
		ft_memset(*buffer, 0, BUFFER_SIZE + 1);
		return (1);
	}
	i = 0;
	ptr = (char *)malloc(BUFFER_SIZE + ft_strlen(*buffer) + 1);
	if (!ptr)
		return (free(*buffer), *buffer = NULL, 0);
	while ((*buffer)[i])
	{
		ptr[i] = (*buffer)[i];
		i++;
	}
	ft_memset(ptr + i, 0, BUFFER_SIZE + 1);
	free(*buffer);
	*buffer = ptr;
	return (1);
}

static char	*return_line(char **buffer, size_t len)
{
	char	*str;
	char	*new_buffer;
	size_t	i;

	if (*buffer == NULL)
		return (NULL);
	i = ft_strlen((const char *)*buffer);
	new_buffer = NULL;
	str = ft_substr((const char *)*buffer, 0, len);
	if (!str)
		return (free(*buffer), *buffer = NULL, NULL);
	if (len < i)
	{
		new_buffer = ft_substr((const char *)*buffer, len, i - len);
		if (!new_buffer)
			return (free(str), free(*buffer), *buffer = NULL, NULL);
		free(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (str);
}

static char	*read_wrp(char **buffer, int fd)
{
	int	i;

	i = 0;
	while (allocation(buffer))
	{
		if (read(fd, *buffer + ft_strlen(*buffer), BUFFER_SIZE) > 0)
		{
			while ((*buffer)[i])
			{
				if ((*buffer)[i] == '\n')
					return (return_line(buffer, ++i));
				i++;
			}
			continue ;
		}
		break ;
	}
	while (*buffer && (*buffer)[i])
	{
		if ((*buffer)[i] == '\n')
			return (return_line(buffer, i + 1));
		i++;
	}
	return (return_line(buffer, i));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			i;
	char		*line;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
	{
		if (buffer)
			return (free(buffer), buffer = NULL, NULL);
		return (NULL);
	}
	line = read_wrp(&buffer, fd);
	if (!line)
		return (0);
	return (line);
}
