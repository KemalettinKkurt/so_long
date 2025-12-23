/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_image	load_image(void *mlx, const char *path)
{
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(mlx, (char *)path, &img.width, &img.height);
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

static void	put_tile(t_game *game, t_image img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img.ptr,
		x * TILE_SIZE, y * TILE_SIZE);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;
	char	tile;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			tile = game->map.grid[y][x];
			if (tile == '1')
				put_tile(game, game->assets.wall, x, y);
			else
				put_tile(game, game->assets.floor, x, y);
			if (tile == 'C')
				put_tile(game, game->assets.collect, x, y);
			else if (tile == 'E')
				put_tile(game, game->assets.exit, x, y);
			x++;
		}
		y++;
	}
	put_tile(game, game->assets.player, game->map.player_x, game->map.player_y);
	return (0);
}
