/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkocakur <kkocakur@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 22:25:23 by kkocakur          #+#    #+#             */
/*   Updated: 2025/12/23 22:25:25 by kkocakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	size_t	i;
	char	*ptr;

	total = count * size;
	if (count && size && total / count != size)
		return (NULL);
	ptr = (char *)malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}
