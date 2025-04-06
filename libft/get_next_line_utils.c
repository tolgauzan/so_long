/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:10:05 by tuzan             #+#    #+#             */
/*   Updated: 2024/11/24 16:10:05 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_free_gnl(char *reads, char *buff)
{
	if (reads)
		free(reads);
	if (buff)
		free(buff);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_append_gnl(char *reads, char *buff)
{
	char	*new_reads;
	size_t	r_len;
	size_t	b_len;

	r_len = ft_strlen_gnl(reads);
	b_len = ft_strlen_gnl(buff);
	new_reads = (char *)malloc((r_len + b_len + 1) * sizeof(char));
	if (!new_reads)
		return (free(reads), NULL);
	if (reads)
		ft_memcpy(new_reads, reads, r_len);
	ft_memcpy(new_reads + r_len, buff, b_len);
	new_reads[r_len + b_len] = '\0';
	free(reads);
	return (new_reads);
}
