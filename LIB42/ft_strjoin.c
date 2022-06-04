/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:29:41 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/09 16:13:29 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cpy;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	cpy = malloc(sizeof(char) * (ft_strlen(s1) + 1 + ft_strlen(s2)));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i] != 0)
	{
		cpy[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != 0)
	{
		cpy[i] = s2[j];
		i++;
		j++;
	}
	cpy[i] = '\0';
	return (cpy);
}
