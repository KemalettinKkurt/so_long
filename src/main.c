/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:23:46 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 01:56:22 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	map->player_x = 0;
	map->player_y = 0;
}

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->moves = 0;
	game->assets.wall.ptr = NULL;
	game->assets.floor.ptr = NULL;
	game->assets.collect.ptr = NULL;
	game->assets.exit.ptr = NULL;
	game->assets.player.ptr = NULL;
	init_map(&game->map);
}

static void	run_game(t_game *game)
{
	render_map(game);
	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long <map.ber>\n", 2);
		return (1);
	}
	init_game(&game);
	if (load_map(argv[1], &game.map))
		error_exit("Invalid map", &game);
	game.mlx = mlx_init();
	if (!game.mlx)
		error_exit("mlx_init failed", &game);
	load_assets(&game);
	if (init_window(&game))
		error_exit("Could not create window", &game);
	run_game(&game);
	close_game(&game);
	return (0);
}
