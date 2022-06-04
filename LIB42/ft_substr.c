/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:19:43 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 15:36:09 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_max_size(const char *s, size_t max)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && i < max)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	length;
	size_t	max_size;

	length = ft_max_size(s, start);
	if (length < start)
		return (ft_strdup(""));
	max_size = ft_max_size(s + start, len);
	temp = ft_calloc(max_size + 1, 1);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s + start, max_size + 1);
	return (temp);
}
