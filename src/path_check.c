/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:23:09 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/23 22:23:12 by kkocakur         ###   ########.fr       */
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

static void	flood_fill(char **grid, int x, int y, t_path_counts *counts)
{
	char	cell;

	if (x < 0 || y < 0 || x >= counts->width || y >= counts->height)
		return ;
	cell = grid[y][x];
	if (cell == '1' || cell == 'V')
		return ;
	if (cell == 'C')
		counts->reach_c++;
	if (cell == 'E')
		counts->reach_e++;
	grid[y][x] = 'V';
	flood_fill(grid, x + 1, y, counts);
	flood_fill(grid, x - 1, y, counts);
	flood_fill(grid, x, y + 1, counts);
	flood_fill(grid, x, y - 1, counts);
}

int	validate_paths(t_map *map)
{
	char			**copy;
	t_path_counts	counts;

	copy = dup_grid(map);
	if (!copy)
		return (1);
	counts.reach_c = 0;
	counts.reach_e = 0;
	counts.width = map->width;
	counts.height = map->height;
	flood_fill(copy, map->player_x, map->player_y, &counts);
	free_grid(copy, map->height);
	return (counts.reach_c != map->collectibles || counts.reach_e < 1);
}
