/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:01:37 by zkansoun          #+#    #+#             */
/*   Updated: 2022/05/31 10:12:53 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIB42/libft.h"

int	between_quotes(char const *str, int i)
{
	int	j;
	int	s_q;
	int	d_q;

	j = i - 1;
	s_q = 0;
	d_q = 0;
	while (j >= 0)
	{
		if (str[j] == 39)
			s_q++;
		if (str[j] == 34)
			d_q++;
		j--;
	}
	if (s_q % 2 == 0 && d_q % 2 == 0)
			return (0);
	j = i + 1;
	while (str[j])
	{
		if (str[j] == 39)
			s_q--;
		if (str[j] == 34)
			d_q--;
		if (s_q == 0 && d_q == 0)
			break ;
		j++;
	}
	if ((s_q == 0)  || (d_q == 0))
		return (1);
	return (0);
}

size_t	get_next_word_q(char const *s, char c)
{
	size_t	limit;

	limit = 0;
	while (s[limit] && !(s[limit] == c && !between_quotes(s, limit)))
		limit++;
	return (limit);
}

char	**free_result_q(char **result, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(result[i++]);
	free(result);
	return (NULL);
}

size_t	count_words_q(char const *s, char c)
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
		else if (s[i - 1] == c && !between_quotes(s, i - 1) && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**result;
	size_t	pieces;
	size_t	i;
	size_t	limit;

	pieces = count_words_q(s, c);
	result = malloc(sizeof(char *) * (pieces + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < pieces)
	{
		while (*s && *s == c)
			s++;
		limit = get_next_word_q(s, c);
		result[i] = ft_substr(s, 0, limit);
		if (!result[i])
			return (free_result_q(result, i));
		s += limit + 1;
		i++;
	}
	result[pieces] = NULL;
	return (result);
}
