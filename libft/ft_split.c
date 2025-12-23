/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (s && *s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*dup_word(char const *start, size_t len)
{
	char	*word;
	size_t	i;

	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_parts(char **arr, size_t filled)
{
	while (filled > 0)
	{
		free(arr[filled - 1]);
		filled--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		i;
	size_t		len;
	size_t		words;

	words = count_words(s, c);
	arr = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len)
		{
			arr[i] = dup_word(s, len);
			if (!arr[i++])
				return (free_parts(arr, i - 1), NULL);
			s += len;
		}
	}
	return (arr);
}

