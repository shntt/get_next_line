/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shitakah <shitakah@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 02:27:27 by shitakah          #+#    #+#             */
/*   Updated: 2025/11/28 10:53:12 by shitakah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_stash(t_stash *st)
{
	if (st->buf)
		free(st->buf);
	st->buf = NULL;
	st->len = 0;
	st->cap = 0;
}

static int	grow_stash(t_stash *st, size_t add)
{
	size_t	required;
	size_t	new_cap;
	char	*new_buf;

	required = st->len + add + 1;
	if (required <= st->cap)
		return (1);
	new_cap = st->cap;
	if (!new_cap)
		new_cap = BUFFER_SIZE + 1;
	while (new_cap < required)
		new_cap *= 2;
	new_buf = malloc(new_cap);
	if (!new_buf)
		return (0);
	if (st->buf)
	{
		ft_memmove_gnl(new_buf, st->buf, st->len);
		free(st->buf);
	}
	st->buf = new_buf;
	st->cap = new_cap;
	return (1);
}

static char	*read_to_stash(int fd, t_stash *st)
{
	char	*buf;
	int		r;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free_stash(st), NULL);
	while (!ft_strchr_gnl(st->buf, '\n'))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r <= 0)
		{
			free(buf);
			if (r < 0)
				free_stash(st);
			return (st->buf);
		}
		if (!grow_stash(st, (size_t)r))
			return (free(buf), free_stash(st), NULL);
		ft_memmove_gnl(st->buf + st->len, buf, (size_t)r);
		st->len += (size_t)r;
		st->buf[st->len] = '\0';
	}
	free(buf);
	return (st->buf);
}

static char	*extract_line(t_stash *st)
{
	size_t	i;

	if (!st->buf || !st->buf[0])
		return (NULL);
	i = 0;
	while (i < st->len && st->buf[i] != '\n')
		i++;
	if (i < st->len && st->buf[i] == '\n')
		i++;
	return (ft_substr_gnl(st->buf, 0, (int)i));
}

char	*get_next_line(int fd)
{
	static t_stash	stash;
	char			*line;
	size_t			consumed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_to_stash(fd, &stash))
		return (NULL);
	line = extract_line(&stash);
	if (!line)
		return (free_stash(&stash), NULL);
	consumed = ft_strlen_gnl(line);
	if (!stash.buf || consumed >= stash.len)
		return (free_stash(&stash), line);
	ft_memmove_gnl(stash.buf, stash.buf + consumed, stash.len - consumed);
	stash.len -= consumed;
	stash.buf[stash.len] = '\0';
	return (line);
}
