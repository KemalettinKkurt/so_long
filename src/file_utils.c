/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_file_content(const char *path)
{
	int		fd;
	char	buffer[1024];
	ssize_t	read_bytes;
	char	*content;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	if (!content)
		return (close(fd), NULL);
	read_bytes = read(fd, buffer, 1023);
	while (read_bytes > 0)
	{
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(content, buffer);
		free(content);
		content = temp;
		if (!content)
			return (close(fd), NULL);
		read_bytes = read(fd, buffer, 1023);
	}
	close(fd);
	if (read_bytes < 0)
		return (free(content), NULL);
	return (content);
}

void	print_move_count(int moves)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putstr_fd("\n", 1);
}

