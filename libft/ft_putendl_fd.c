/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 04:19:23 by tuzan             #+#    #+#             */
/*   Updated: 2024/10/23 04:19:23 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	ssize_t	bytes_written;
	size_t	strlen;

	if (s || fd >= 0)
	{
		strlen = ft_strlen(s);
		bytes_written = write(fd, s, strlen);
		while (bytes_written != -1 && (size_t)bytes_written < strlen)
		{
			strlen -= bytes_written;
			s += bytes_written;
			bytes_written = write(fd, s, strlen);
		}
		ft_putchar_fd('\n', fd);
	}
}
