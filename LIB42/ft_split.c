/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:01:37 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 15:40:34 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_next_word(char const *s, char c)
{
	size_t	limit;

	limit = 0;
	while (s[limit] && s[limit] != c)
		limit++;
	return (limit);
}

char	**free_result(char **result, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(result[i++]);
	free(result);
	return (NULL);
}

size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i])
	{
		if (!i)
			words++;
		else if (s[i - 1] == c && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	pieces;
	size_t	i;
	size_t	limit;

	pieces = count_words(s, c);
	result = malloc(sizeof(char *) * (pieces + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < pieces)
	{
		while (*s && *s == c)
			s++;
		limit = get_next_word(s, c);
		result[i] = ft_substr(s, 0, limit);
		if (!result[i])
			return (free_result(result, i));
		s += limit + 1;
		i++;
	}
	result[pieces] = NULL;
	return (result);
}
