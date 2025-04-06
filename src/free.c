/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:30:25 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:30:25 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	free_visited_map(char **v_map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(v_map[i++]);
	free(v_map);
}

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->t_map)
	{
		while (i < map->rows)
			free(map->t_map[i++]);
		free(map->t_map);
	}
	free(map);
}

static void	free_images(void *mlx, t_img *images)
{
	if (images->wall)
		mlx_destroy_image(mlx, images->wall);
	if (images->player)
		mlx_destroy_image(mlx, images->player);
	if (images->background)
		mlx_destroy_image(mlx, images->background);
	if (images->collectible)
		mlx_destroy_image(mlx, images->collectible);
	if (images->exit)
		mlx_destroy_image(mlx, images->exit);
}

static void	free_resources(t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->images)
		{
			if (game->window)
				free_images(game->mlx, game->images);
			free(game->images);
		}
		if (game->window)
			mlx_destroy_window(game->mlx, game->window);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free(game);
	}
}

void	free_exit(t_game *game, char *message, int is_error)
{
	if (game)
		free_resources(game);
	if (is_error)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
	exit(EXIT_SUCCESS);
}
