/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
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

static void	free_rows(char **rows)
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

static int	is_border_wall(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
				if (map->grid[y][x] != '1')
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	validate_counts(t_map *map)
{
	if (map->exits != 1 || map->players != 1 || map->collectibles < 1)
		return (1);
	if (is_border_wall(map))
		return (1);
	if (validate_paths(map))
		return (1);
	return (0);
}

static int	load_grid(char **rows, t_map *map)
{
	int	y;
	int	x;

	map->height = 0;
	while (rows[map->height])
		map->height++;
	map->grid = (char **)ft_calloc(map->height, sizeof(char *));
	if (!map->grid)
		return (1);
	y = 0;
	while (y < map->height)
	{
		map->grid[y] = ft_strdup(rows[y]);
		if (!map->grid[y])
			return (free_map(map), 1);
		if ((int)ft_strlen(rows[y]) != map->width)
			return (free_map(map), 1);
		x = -1;
		while (++x < map->width)
		{
			if (!ft_strchr("01CEP", rows[y][x]))
				return (free_map(map), 1);
		}
		y++;
	}
	return (0);
}

static int	parse_rows(char **rows, t_map *map)
{
	int	x;
	int	y;

	map->width = ft_strlen(rows[0]);
	if (load_grid(rows, map))
		return (1);
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
				map->grid[y][x] = '0';
			}
			else if (map->grid[y][x] == 'C')
				map->collectibles++;
			else if (map->grid[y][x] == 'E')
				map->exits++;
		}
	}
	return (validate_counts(map));
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
		return (free_rows(rows), 1);
	if (parse_rows(rows, map))
		return (free_rows(rows), 1);
	free_rows(rows);
	return (0);
}

