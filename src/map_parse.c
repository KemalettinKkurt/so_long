/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:23:23 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 03:15:42 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (1);
	return (ft_strncmp(path + len - 4, ".ber", 4));
}

static int	load_grid(char **rows, t_map *map, int width)
{
	int	y;
	int	x;

	map->width = width;
	map->height = 0;
	while (rows[map->height])
		map->height++;
	if (width > 30 || map->height > 16)
		return (1);
	map->grid = ft_calloc(map->height, sizeof(char *));
	if (!map->grid)
		return (1);
	y = -1;
	while (++y < map->height)
	{
		map->grid[y] = ft_strdup(rows[y]);
		if (!map->grid[y] || (int)ft_strlen(rows[y]) != width)
			return (free_map(map), 1);
		x = -1;
		while (++x < width)
			if (!ft_strchr("01CEP", rows[y][x]))
				return (free_map(map), 1);
	}
	return (0);
}

static void	count_elements(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->grid[y][x] == 'P')
			{
				map->players++;
				map->player_x = x;
				map->player_y = y;
			}
			else if (map->grid[y][x] == 'C')
				map->collectibles++;
			else if (map->grid[y][x] == 'E')
				map->exits++;
		}
	}
}

static int	parse_rows(char **rows, t_map *map)
{
	int	width;

	width = ft_strlen(rows[0]);
	if (load_grid(rows, map, width))
		return (1);
	count_elements(map);
	if (validate_counts(map))
		return (1);
	map->grid[map->player_y][map->player_x] = '0';
	return (0);
}

int	load_map(const char *path, t_map *map)
{
	char	*content;
	char	**rows;

	if (check_extension(path))
		return (1);
	content = read_file_content(path);
	if (!content || !*content)
		return (free(content), 1);
	rows = ft_split(content, '\n');
	free(content);
	if (!rows || !rows[0])
	{
		free_rows(rows);
		return (1);
	}
	if (parse_rows(rows, map))
	{
		free_rows(rows);
		return (1);
	}
	free_rows(rows);
	return (0);
}
