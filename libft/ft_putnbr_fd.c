/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:25:17 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 01:25:52 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_unsigned(unsigned int nb, int fd)
{
	char	c;

	if (nb >= 10)
		put_unsigned(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		put_unsigned((unsigned int)(-n), fd);
	}
	else
		put_unsigned((unsigned int)n, fd);
}
