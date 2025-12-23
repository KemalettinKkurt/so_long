/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->assets.wall.ptr)
		mlx_destroy_image(game->mlx, game->assets.wall.ptr);
	if (game->assets.floor.ptr)
		mlx_destroy_image(game->mlx, game->assets.floor.ptr);
	if (game->assets.collect.ptr)
		mlx_destroy_image(game->mlx, game->assets.collect.ptr);
	if (game->assets.exit.ptr)
		mlx_destroy_image(game->mlx, game->assets.exit.ptr);
	if (game->assets.player.ptr)
		mlx_destroy_image(game->mlx, game->assets.player.ptr);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

static void	clean_game(t_game *game)
{
	destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(&game->map);
}

void	error_exit(const char *message, t_game *game)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd((char *)message, 2);
		ft_putstr_fd("\n", 2);
	}
	clean_game(game);
	exit(1);
}

int	close_game(t_game *game)
{
	clean_game(game);
	exit(0);
	return (0);
}

