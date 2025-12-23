/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:24:03 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 01:46:32 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*append_buffer(char *content, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(content, buffer);
	free(content);
	return (temp);
}

char	*read_file_content(const char *path)
{
	int		fd;
	ssize_t	bytes;
	char	buf[1024];
	char	*res;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = ft_strdup("");
	bytes = read(fd, buf, 1023);
	while (res && bytes > 0)
	{
		buf[bytes] = '\0';
		res = append_buffer(res, buf);
		bytes = read(fd, buf, 1023);
	}
	close(fd);
	if (bytes < 0)
		return (free(res), NULL);
	return (res);
}

void	print_move_count(int moves)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putstr_fd("\n", 1);
}
