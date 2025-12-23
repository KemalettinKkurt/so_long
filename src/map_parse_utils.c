/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:23:36 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/23 22:23:39 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_rows(char **rows)
{
	int	i;

	if (!rows)
		return ;
	i = 0;
	while (rows[i])
	{
		free(rows[i]);
		i++;
	}
	free(rows);
}

int	is_border_wall(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((y == 0 || y == map->height - 1 || x == 0
					|| x == map->width - 1) && map->grid[y][x] != '1')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_counts(t_map *map)
{
	if (map->exits != 1 || map->players != 1 || map->collectibles < 1)
		return (1);
	if (is_border_wall(map))
		return (1);
	if (validate_paths(map))
		return (1);
	return (0);
}
