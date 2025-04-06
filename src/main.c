/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:30:46 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:30:46 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include <X11/X.h>

static void	init_game_window(t_game *game)
{
	init_mlx_and_window(game);
	load_images(game);
	render(game);
	if (mlx_string_put(game->mlx, game->window,
			(game->map->cols * TILE_SIZE - 60) / 2,
			(game->map->rows * TILE_SIZE / 2),
			0xFFFFFF, "Start Game!") != 0)
		free_exit(game, "Failed to render string", 1);
}

static void	check_map(t_game *game, const char *file_path)
{
	create_map(game, file_path);
	check_map_shape(game);
	check_map_elements(game);
	check_map_walls(game);
	check_map_valid_path(game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc != 2)
		free_exit(NULL, "Usage: ./so_long 'path/file.ber'", 1);
	check_map_file(argv[1]);
	game = init_game();
	check_map(game, argv[1]);
	init_game_window(game);
	mlx_hook(game->window, KeyPress, KeyPressMask, key_events, game);
	mlx_hook(game->window, DestroyNotify, 0, close_game, game);
	mlx_loop(game->mlx);
	return (0);
}
