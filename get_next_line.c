/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shitakah <shitakah@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 02:27:27 by shitakah          #+#    #+#             */
/*   Updated: 2025/11/13 22:14:19 by shitakah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init_rest(char **rest)
{
	if (!*rest)
	{
		*rest = ft_strdup("");
		if (!*rest)
			return (0);
	}
	return (1);
}

static int	read_into_rest(int fd, char **rest)
{
	char	*buf;
	ssize_t	rc;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	rc = read(fd, buf, BUFFER_SIZE);
	while (rc > 0)
	{
		buf[rc] = '\0';
		*rest = join_and_free(*rest, buf);
		if (!*rest)
			return (free(buf), -1);
		if (ft_strchr(*rest, '\n'))
			break ;
		rc = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (rc < 0)
		return (-1);
	if (rc == 0 && (!*rest || **rest == '\0'))
		return (0);
	return (1);
}

static char	*extract_line(char **rest)
{
	size_t	i;
	char	*line;

	i = 0;
	while ((*rest)[i] != '\n' && (*rest)[i] != '\0')
		i++;
	if ((*rest)[i] == '\n')
		i++;
	line = ft_substr(*rest, 0, i);
	if (!line)
	{
		free(*rest);
		*rest = NULL;
		return (NULL);
	}
	return (line);
}

static int	update_rest(char **rest)
{
	size_t	i;
	char	*next;

	i = 0;
	while ((*rest)[i] != '\n' && (*rest)[i] != '\0')
		i++;
	if ((*rest)[i] == '\0')
	{
		free(*rest);
		*rest = NULL;
		return (1);
	}
	next = ft_strdup(*rest + i + 1);
	if (!next)
	{
		free(*rest);
		*rest = NULL;
		return (0);
	}
	free(*rest);
	*rest = next;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0 || !init_rest(&rest))
		return (NULL);
	status = read_into_rest(fd, &rest);
	if (status <= 0)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line = extract_line(&rest);
	if (!line)
		return (NULL);
	if (!update_rest(&rest))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

//#include <stdio.h>
//#include <fcntl.h>
//int	main(void)
//{
//	int		fd;
//	char	*line1;
//	char	*line2;
//	char	*line3;
//	fd = open("test.txt", O_RDONLY);
//	line1 = get_next_line(fd);
//	line2 = get_next_line(fd);
//	line3 = get_next_line(fd);
//	close(fd);
//	free(line1);
//	free(line2);
//	free(line3);
//}