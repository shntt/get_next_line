/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shitakah <shitakah@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 01:15:08 by shitakah          #+#    #+#             */
/*   Updated: 2025/11/28 10:52:51 by shitakah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*alloc_empty(void)
{
	char	*r;

	r = malloc(1);
	if (!r)
		return (NULL);
	r[0] = '\0';
	return (r);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*ft_substr_gnl(char *s, int start, int len)
{
	char	*r;
	int		i;
	int		size;

	if (!s || len < 0)
		return (NULL);
	size = (int)ft_strlen_gnl(s);
	if (start >= size)
		return (alloc_empty());
	if (start + len > size)
		len = size - start;
	r = malloc(len + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

void	ft_memmove_gnl(char *dst, char *src, size_t n)
{
	size_t	i;

	if (!dst || !src || dst == src)
		return ;
	if (dst < src)
	{
		i = 0;
		while (i < n)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			dst[n] = src[n];
		}
	}
}
