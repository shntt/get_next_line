/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shitakah <shitakah@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:53:30 by shitakah          #+#    #+#             */
/*   Updated: 2025/12/01 21:09:48 by shitakah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef GNL_MAX_FD
#  define GNL_MAX_FD 1024
# endif

/**
 * @brief Internal buffer tracker used by get_next_line.
 * @param buf Pointer to the allocated storage (NULL when empty)
 * @param len Number of bytes currently stored in buf
 * @param cap Total allocated capacity of buf
 */
typedef struct s_stash
{
	char	*buf;
	size_t	len;
	size_t	cap;
}			t_stash;

/**
 * @brief Read the next line from the file descriptor.
 * @param fd File descriptor returned by open/read
 * @return Newly allocated string containing the next line or NULL on EOF/error
 */
char		*get_next_line(int fd);
/**
 * @brief Create a substring copy from s.
 * @param s Source string
 * @param start Starting index within s
 * @param len Maximum number of characters to copy
 * @return Newly allocated substring or NULL on failure
 */
char		*ft_substr_gnl(char *s, int start, int len);
/**
 * @brief Locate the first occurrence of c in s.
 * @param s String to scan (can be NULL)
 * @param c Character to find
 * @return Pointer inside s where c was found, or NULL if absent
 */
char		*ft_strchr_gnl(char *s, int c);
/**
 * @brief Compute the length of s safely.
 * @param s String whose length is requested (can be NULL)
 * @return Number of characters in s, or 0 if s is NULL
 */
size_t		ft_strlen_gnl(char *s);
/**
 * @brief Safe memmove variant used by get_next_line helpers.
 * @param dst Destination buffer
 * @param src Source buffer
 * @param n Number of bytes to copy
 * @return Nothing
 */
void		ft_memmove_gnl(char *dst, char *src, size_t n);

#endif
