/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:30:51 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:30:51 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>

static void	*load_image(t_game *game, char *image_path)
{
	void	*image;
	int		w;
	int		h;

	image = mlx_xpm_file_to_image(game->mlx, image_path, &w, &h);
	if (!image)
		free_exit(game, "Image loading failed", 1);
	return (image);
}

void	load_images(t_game *game)
{
	game->images->player = load_image(game, "textures/player.xpm");
	game->images->wall = load_image(game, "textures/wall.xpm");
	game->images->exit = load_image(game, "textures/exit.xpm");
	game->images->collectible = load_image(game, "textures/collectible.xpm");
	game->images->background = load_image(game, "textures/background.xpm");
}

static void	*get_tile_image(t_game *game, int tile)
{
	void	*image;

	image = NULL;
	if (tile == '1')
		image = game->images->wall;
	else if (tile == 'E')
		image = game->images->exit;
	else if (tile == 'C')
		image = game->images->collectible;
	else if (tile == '0' || tile == 'P')
		image = game->images->background;
	if (!image)
		free_exit(game, "image could not be suppressed", 1);
	return (image);
}

void	render(t_game *game)
{
	int		row;
	int		col;
	void	*image;

	row = 0;
	while (game->map->t_map[row] != NULL)
	{
		col = 0;
		while (game->map->t_map[row][col] != '\0')
		{
			image = get_tile_image(game, game->map->t_map[row][col]);
			mlx_put_image_to_window(game->mlx, game->window,
				image, col * TILE_SIZE, row * TILE_SIZE);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(game->mlx, game->window,
		game->images->player,
		game->player.col * TILE_SIZE,
		game->player.row * TILE_SIZE);
}
