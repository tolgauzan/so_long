/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:30:57 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:30:57 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 32
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
	int	color_code;
}	t_color;

typedef struct s_player
{
	int	row;
	int	col;
	int	move_count;
	int	total_points;
}	t_player;

typedef struct s_map
{
	char	**t_map;
	int		rows;
	int		cols;
	int		player_count;
	int		collec_count;
	int		exit_count;
}	t_map;

typedef struct s_img
{
	void	*wall;
	void	*player;
	void	*background;
	void	*collectible;
	void	*exit;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		*map;
	t_img		*images;
	t_player	player;
	t_color		color;
}	t_game;

//Initialization
t_game	*init_game(void);
t_map	*init_map(void);
t_img	*init_images(void);
t_color	init_color(void);
void	init_mlx_and_window(t_game *game);
//Memory management
void	free_exit(t_game *game, char *message, int is_error);
void	free_visited_map(char **v_map, int rows);
//Map handling
void	create_map(t_game *game, const char *file_path);
void	check_map_file(const char *file_path);
//Map validation
void	check_map_shape(t_game *game);
void	check_map_elements(t_game *game);
void	check_map_walls(t_game *game);
void	check_map_valid_path(t_game *game);
//Render
void	load_images(t_game *game);
void	render_map(t_game *game);
void	render_player(t_game *game);
//Events
int		close_game(t_game *game);
int		key_events(int key, t_game *game);
int		get_dynamic_color(t_color *color);
#endif
