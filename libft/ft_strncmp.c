/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:24:32 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/24 01:27:32 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (u1[i] || u2[i]))
	{
		if (u1[i] != u2[i])
			return (u1[i] - u2[i]);
		i++;
	}
	return (0);
}
