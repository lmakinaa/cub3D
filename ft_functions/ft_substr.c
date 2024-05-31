/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:46:01 by miguiji           #+#    #+#             */
/*   Updated: 2023/11/10 23:45:23 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_substr(const char *str, int start, int len)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (NULL);
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	ptr = heap_control(1, len + 1, 0, 0);
	if (ptr == NULL)
		return (0);
	while (i < len && (str + start)[i])
	{
		ptr[i] = (str + start)[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
