/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:29:31 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:29:31 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	check_filename(const char *filename)
{
	char	*dot_pos;

	if (ft_strlen(filename) <= 4)
		free_exit(NULL, "Invalid file name", 1);
	dot_pos = ft_strchr(filename, '.');
	if (!dot_pos)
		free_exit(NULL, "Invalid file name, no extention found", 1);
	if (ft_strncmp(dot_pos, ".ber", 4) != 0 || dot_pos[4] != '\0')
		free_exit(NULL, "File must have a .ber extension", 1);
}

void	check_map_file(const char *file_path)
{
	char	*filename;
	char	*line;
	int		fd;

	if (!ft_strnstr(file_path, "maps/", ft_strlen(file_path)))
		free_exit(NULL, "Maps directory does not exist", 1);
	filename = ft_strrchr(file_path, '/');
	if (filename && filename[1] != '\0')
		filename++;
	else
		free_exit(NULL, "Invalid file name, no file found after 'maps/'", 1);
	check_filename(filename);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		free_exit(NULL, "File does not exits or connot be opened", 1);
	line = get_next_line(fd);
	if (!line)
		free_exit(NULL, "File is empty", 1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
