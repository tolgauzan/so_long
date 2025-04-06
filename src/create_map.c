/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:29:48 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:29:48 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static void	gnl_cleaner(int fd)
{
	char	*dummy;

	dummy = get_next_line(fd);
	while (dummy)
	{
		free(dummy);
		dummy = get_next_line(fd);
	}
	free(dummy);
}

static void	alloc_and_count_rows(t_game *game, const char *file_path)
{
	char	*line;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		free_exit(game, "File descriptor failed", 1);
	line = get_next_line(fd);
	while (line)
	{
		game->map->rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (game->map->rows < 4)
		free_exit(game, "Mandatory objects cannot fit on the map", 1);
	game->map->t_map = (char **)malloc(
			(game->map->rows + 1) * sizeof(char *));
	if (!game->map->t_map)
		free_exit(game, "T_Map memory allocation failed", 1);
}

static void	read_map(t_game *game, int fd)
{
	char	*trimmed_line;
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, "\r\n");
		free(line);
		if (!trimmed_line)
		{
			gnl_cleaner(fd);
			free_exit(game, "Memory allocation failed", 1);
		}
		game->map->t_map[i++] = trimmed_line;
		line = get_next_line(fd);
	}
	free(line);
	game->map->t_map[i] = NULL;
}

void	create_map(t_game *game, const char *file_path)
{
	int	fd;

	alloc_and_count_rows(game, file_path);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		free_exit(game, "Failed to open file", 1);
	read_map(game, fd);
	close(fd);
}
