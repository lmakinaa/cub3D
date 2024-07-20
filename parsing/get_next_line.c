/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:01:07 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/20 13:26:48 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	allocation(char **buffer)
{
	char	*ptr;
	int		i;

	if (!(*buffer))
	{
		*buffer = (char *)heap_control(M_ALLOC, BUFFER_SIZE + 1, 0, 0);
		if (!(*buffer))
			return (0);
		ft_memset(*buffer, 0, BUFFER_SIZE + 1);
		return (1);
	}
	i = 0;
	ptr = (char *)heap_control(M_ALLOC, BUFFER_SIZE + ft_strlen(*buffer) + 1, 0, 0);
	if (!ptr)
		return (heap_control(M_DEL, 0, *buffer, 0), *buffer = NULL, 0);
	while ((*buffer)[i])
	{
		ptr[i] = (*buffer)[i];
		i++;
	}
	ft_memset(ptr + i, 0, BUFFER_SIZE + 1);
	heap_control(M_DEL, 0, *buffer, 0);
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
		return (heap_control(M_DEL, 0, *buffer, 0), *buffer = NULL, NULL);
	if (len < i)
	{
		new_buffer = ft_substr((const char *)*buffer, len, i - len);
		if (!new_buffer)
			return (heap_control(M_DEL, 0, str, 0), heap_control(M_DEL, 0, *buffer, 0), *buffer = NULL, NULL);
		heap_control(M_DEL, 0, *buffer, 0);
		*buffer = new_buffer;
	}
	else
	{
		heap_control(M_DEL, 0, *buffer, 0);
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
			return (heap_control(M_DEL, 0, buffer, 0), buffer = NULL, NULL);
		return (NULL);
	}
	line = read_wrp(&buffer, fd);
	if (!line)
		return (0);
	return (line);
}
