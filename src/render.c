/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:22:57 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/23 22:23:16 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_image	load_image(void *mlx, const char *path)
{
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(mlx, (char *)path,
			&img.width, &img.height);
	return (img);
}

void	load_assets(t_game *game)
{
	game->assets.wall = load_image(game->mlx, "textures/wall.xpm");
	game->assets.floor = load_image(game->mlx, "textures/floor.xpm");
	game->assets.collect = load_image(game->mlx, "textures/collect.xpm");
	game->assets.exit = load_image(game->mlx, "textures/exit.xpm");
	game->assets.player = load_image(game->mlx, "textures/player.xpm");
	if (!game->assets.wall.ptr || !game->assets.floor.ptr
		|| !game->assets.collect.ptr || !game->assets.exit.ptr
		|| !game->assets.player.ptr)
		error_exit("Failed to load textures", game);
}

int	init_window(t_game *game)
{
	int	width;
	int	height;

	width = game->map.width * TILE_SIZE;
	height = game->map.height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, width, height, "so_long");
	if (!game->win)
		return (1);
	return (0);
}

static void	put_tile(t_game *game, char tile, int x, int y)
{
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.wall.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->assets.floor.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
	if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.collect.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->assets.exit.ptr,
			x * TILE_SIZE, y * TILE_SIZE);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			put_tile(game, game->map.grid[y][x], x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->assets.player.ptr,
		game->map.player_x * TILE_SIZE, game->map.player_y * TILE_SIZE);
	return (0);
}
