/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:48:41 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/17 11:18:58 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*p;
	unsigned int	i;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[i]))
		i--;
	p = (char *)malloc(i + 2);
	if (!p)
		return (NULL);
	if (*s1)
		ft_strlcpy(p, s1, i + 2);
	else
		p[i] = '\0';
	return (p);
}
