/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:10:10 by tuzan             #+#    #+#             */
/*   Updated: 2024/11/24 16:10:10 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_update(char *reads)
{
	char	*new_reads;
	size_t	i;
	size_t	j;

	i = 0;
	while (reads[i] != '\n' && reads[i] != '\0')
		i++;
	if (reads[i] == '\0')
		return (ft_free_gnl(reads, NULL));
	new_reads = (char *)malloc((ft_strlen_gnl(reads) - i) * sizeof(char));
	if (!new_reads)
		return (ft_free_gnl(reads, NULL));
	j = 0;
	while (reads[++i])
		new_reads[j++] = reads[i];
	new_reads[j] = '\0';
	free(reads);
	return (new_reads);
}

static char	*ft_parse(char *reads)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (reads[0] == '\0')
		return (NULL);
	while (reads[i] != '\n' && reads[i] != '\0')
		i++;
	if (reads[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (reads[j] != '\n' && reads[j] != '\0')
	{
		line[j] = reads[j];
		j++;
	}
	if (reads[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static char	*ft_read(int fd, char *reads)
{
	char	*buff;
	ssize_t	b_read;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (ft_free_gnl(reads, NULL));
	b_read = 1;
	while (b_read > 0 && !ft_strchr_gnl(reads, '\n'))
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
			return (ft_free_gnl(reads, buff));
		buff[b_read] = '\0';
		reads = ft_append_gnl(reads, buff);
		if (!reads)
			return (ft_free_gnl(reads, buff));
	}
	free(buff);
	return (reads);
}

char	*get_next_line(int fd)
{
	static char	*reads;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reads = ft_read(fd, reads);
	if (!reads)
		return (NULL);
	line = ft_parse(reads);
	if (!line)
	{
		free(reads);
		reads = NULL;
		return (NULL);
	}
	reads = ft_update(reads);
	return (line);
}
