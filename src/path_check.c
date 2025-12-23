/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static char	**dup_grid(t_map *map)
{
	char	**copy;
	int		y;

	copy = (char **)ft_calloc(map->height, sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		copy[y] = ft_strdup(map->grid[y]);
		if (!copy[y])
		{
			free_grid(copy, y);
			return (NULL);
		}
		y++;
	}
	return (copy);
}

static void	flood_fill(char **grid, int x, int y, t_map *map,
				int *reach_c, int *reach_e)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == 'C')
		(*reach_c)++;
	if (grid[y][x] == 'E')
	{
		(*reach_e)++;
		return ;
	}
	grid[y][x] = 'V';
	flood_fill(grid, x + 1, y, map, reach_c, reach_e);
	flood_fill(grid, x - 1, y, map, reach_c, reach_e);
	flood_fill(grid, x, y + 1, map, reach_c, reach_e);
	flood_fill(grid, x, y - 1, map, reach_c, reach_e);
}

int	validate_paths(t_map *map)
{
	char	**copy;
	int		reach_c;
	int		reach_e;

	copy = dup_grid(map);
	if (!copy)
		return (1);
	reach_c = 0;
	reach_e = 0;
	flood_fill(copy, map->player_x, map->player_y, map, &reach_c, &reach_e);
	free_grid(copy, map->height);
	if (reach_c != map->collectibles)
		return (1);
	if (reach_e < 1)
		return (1);
	return (0);
}

