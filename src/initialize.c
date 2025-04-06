/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:30:40 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:30:40 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "mlx.h"

t_color	init_color(void)
{
	t_color	color;

	color.r = 180;
	color.g = 200;
	color.b = 220;
	color.a = 250;
	color.color_code = 0;
	return (color);
}

t_img	*init_images(void)
{
	t_img	*images;

	images = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!images)
		return (NULL);
	return (images);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	return (map);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		free_exit(NULL, "Game memory allocation failed", 1);
	game->map = init_map();
	if (!game->map)
		free_exit(game, "Map memory allocation failed", 1);
	game->images = init_images();
	if (!game->images)
		free_exit(game, "Img memory allocation failed", 1);
	game->color = init_color();
	game->player.move_count = 1;
	return (game);
}

void	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_exit(game, "MLX initialization failed", 1);
	game->window = mlx_new_window(game->mlx, (game->map->cols * TILE_SIZE),
			(game->map->rows * TILE_SIZE), "./so_long");
	if (!game->window)
		free_exit(game, "Window creation failed", 1);
}
