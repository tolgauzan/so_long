/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:29:42 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:29:42 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static char	**create_visited_map(t_game *game)
{
	char	**v_map;
	int		i;

	v_map = (char **)ft_calloc(game->map->rows, sizeof(char *));
	if (!v_map)
		free_exit(game, "VMap memory allocation failed", 1);
	i = 0;
	while (i < game->map->rows)
	{
		v_map[i] = ft_calloc(game->map->cols, sizeof(char));
		if (!v_map[i])
		{
			free_visited_map(v_map, i);
			free_exit(game, "VMap memory allocation failed", 1);
		}
		ft_memcpy(v_map[i], game->map->t_map[i], game->map->cols);
		i++;
	}
	return (v_map);
}

static void	dfs(char **v_map, int *remaining_target, int row, int col)
{
	if (v_map[row][col] == '1' || *remaining_target == 0)
		return ;
	if (v_map[row][col] == 'E' || v_map[row][col] == 'C')
		(*remaining_target)--;
	v_map[row][col] = '1';
	dfs(v_map, remaining_target, row, col + 1);
	dfs(v_map, remaining_target, row, col - 1);
	dfs(v_map, remaining_target, row + 1, col);
	dfs(v_map, remaining_target, row - 1, col);
}

void	check_map_valid_path(t_game *game)
{
	char	**v_map;
	int		remaining_target;

	remaining_target = game->map->c_count + game->map->e_count;
	v_map = create_visited_map(game);
	dfs(v_map, &remaining_target, game->player.row, game->player.col);
	if (remaining_target != 0)
	{
		free_visited_map(v_map, game->map->rows);
		free_exit(game, "Unreachable map or missing collectibles/exits", 1);
	}
	free_visited_map(v_map, game->map->rows);
}
