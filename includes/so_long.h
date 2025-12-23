/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 01:52:55 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"

# define TILE_SIZE 64

typedef struct s_image
{
	void	*ptr;
	int		width;
	int		height;
}	t_image;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_assets
{
	t_image	wall;
	t_image	floor;
	t_image	collect;
	t_image	exit;
	t_image	player;
}	t_assets;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_assets	assets;
	int			moves;
}	t_game;

typedef struct s_path_counts
{
	int	reach_c;
	int	reach_e;
	int	width;
	int	height;
}	t_path_counts;

/* map / parsing */
int		load_map(const char *path, t_map *map);
void	free_map(t_map *map);
void	free_rows(char **rows);
void	free_map_grid(char **grid, int height);

/* map / parsing utils */
int		is_border_wall(t_map *map);
int		validate_counts(t_map *map);

/* path validation */
int		validate_paths(t_map *map);

/* rendering */
int		render_map(t_game *game);
int		init_window(t_game *game);
void	load_assets(t_game *game);
void	destroy_images(t_game *game);

/* hooks */
int		handle_key(int keysym, t_game *game);
int		close_game(t_game *game);

/* utils */
void	error_exit(const char *message, t_game *game);
void	print_move_count(int moves);
char	*read_file_content(const char *path);
void	clean_game(t_game *game);

#endif
