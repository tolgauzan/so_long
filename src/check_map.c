/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:29:37 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:29:37 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

void	check_map_shape(t_game *game)
{
	int	i;
	int	curr_row_len;

	i = 0;
	game->map->cols = (int)ft_strlen(game->map->t_map[0]);
	if (game->map->cols < 4)
		free_exit(game, "Mandatory objects cannot fit on the map", 1);
	while (i < game->map->rows)
	{
		curr_row_len = (int)ft_strlen(game->map->t_map[i]);
		if (curr_row_len != game->map->cols)
			free_exit(game, "Map is not rectangular", 1);
		i++;
	}
}

static void	check_map_cell(t_game *game)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	while (++i < game->map->rows)
	{
		j = -1;
		while (++j < game->map->cols)
		{
			c = game->map->t_map[i][j];
			if (c != '0' && c != '1' && c != 'C' && c != 'P' && c != 'E')
				free_exit(game, "Invalid character found in map", 1);
			if (c == 'C')
				game->map->c_count++;
			else if (c == 'E')
				game->map->e_count++;
			else if (c == 'P')
			{
				game->map->p_count++;
				game->player.row = i;
				game->player.col = j;
			}
		}
	}
}

void	check_map_elements(t_game *game)
{
	check_map_cell(game);
	if (game->map->e_count != 1)
		free_exit(game, "There must be one exit in the map", 1);
	if (game->map->p_count != 1)
		free_exit(game, "There must be one player on the map", 1);
	if (game->map->c_count < 1)
		free_exit(game, "No collectible items on the map", 1);
}

void	check_map_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->cols)
	{
		if (game->map->t_map[0][i] != '1' ||
			game->map->t_map[game->map->rows - 1][i] != '1')
			free_exit(game, "Map must be surrounded by walls", 1);
		i++;
	}
	i = 0;
	while (i < game->map->rows)
	{
		if (game->map->t_map[i][0] != '1' ||
			game->map->t_map[i][game->map->cols - 1] != '1')
			free_exit(game, "Map must be surrounded by walls", 1);
		i++;
	}
}
