/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:24:10 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 01:32:06 by kkocakur         ###   ########.fr       */
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

void	free_map_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
		{
			free(grid[i]);
			grid[i] = NULL;
		}
		i++;
	}
	free(grid);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_map_grid(map->grid, map->height);
	map->grid = NULL;
}

void	clean_game(t_game *game)
{
	destroy_images(game);
	if (game->win && game->mlx)
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
