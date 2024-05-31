/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:45:12 by miguiji           #+#    #+#             */
/*   Updated: 2024/05/21 22:05:40 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	copy(char *ptr, const char *s)
{
	while (*ptr)
		ptr++;
	while (*s)
	{
		*ptr = *s;
		ptr++;
		s++;
	}
	*ptr = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = heap_control(1, len + 1, 0, 0);
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '\0';
	copy(ptr, s1);
	copy(ptr, s2);
	return (ptr);
}
