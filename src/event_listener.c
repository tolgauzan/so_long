/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:29:53 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:29:53 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <X11/keysym.h>

int	close_game(t_game *game)
{
	free_exit(game, "Game closed", 0);
	return (0);
}

void	display_score(t_game *game)
{
	char	*score;
	char	*score_text;
	int		x;
	int		y;

	score = ft_itoa(game->player.total_points);
	if (!score)
		free_exit(game, "Score failed", 1);
	score_text = ft_strjoin("Total Point ", score);
	free(score);
	if (!score_text)
		free_exit(game, "Score failed", 1);
	x = (game->map->cols / 2) * TILE_SIZE - TILE_SIZE;
	y = (game->map->rows - 1) * TILE_SIZE + TILE_SIZE / 2;
	if (mlx_string_put(game->mlx, game->window, x, y,
			game->color.color_code, score_text) != 0)
		free_exit(game, "Failed to render score", 1);
	free(score_text);
}

static void	update_game_state(t_game *game)
{
	ft_putstr_fd("Player Move Count: ", 1);
	ft_putnbr_fd(game->player.move_count++, 1);
	ft_putchar_fd('\n', 1);
	game->color.color_code = get_dynamic_color(&game->color);
	if (game->map->t_map[game->player.row][game->player.col] == 'C')
	{
		game->map->t_map[game->player.row][game->player.col] = '0';
		game->map->c_count--;
		game->player.total_points += 10;
	}
	if (game->map->t_map[game->player.row][game->player.col] == 'E' &&
		game->map->c_count == 0)
		free_exit(game, "Finish game", 0);
}

static void	press_key(int key, t_game *game)
{
	int	row;
	int	col;

	row = game->player.row;
	col = game->player.col;
	if (key == XK_w || key == XK_Up)
		row--;
	else if (key == XK_s || key == XK_Down)
		row++;
	else if (key == XK_a || key == XK_Left)
		col--;
	else if (key == XK_d || key == XK_Right)
		col++;
	else if (key == XK_Escape)
		free_exit(game, "Game Closed", 0);
	if (game->map->t_map[row][col] != '1')
	{
		game->player.row = row;
		game->player.col = col;
		update_game_state(game);
	}
}

int	key_events(int key, t_game *game)
{
	if (key == XK_w || key == XK_a || key == XK_s
		|| key == XK_d || key == XK_Escape || key == XK_Up
		|| key == XK_Down || key == XK_Left || key == XK_Right)
	{
		press_key(key, game);
		render(game);
		display_score(game);
	}
	return (0);
}
