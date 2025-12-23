/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.collectibles = 0;
	game->map.exits = 0;
	game->map.players = 0;
	game->map.player_x = 0;
	game->map.player_y = 0;
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
	render_map(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	close_game(&game);
	return (0);
}

