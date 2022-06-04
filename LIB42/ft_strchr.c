/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:57:41 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/09 17:11:02 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != (char)c)
		i++;
	if (s[i] == 0 && c == 0)
		return ((char *)(s + i));
	if (s[i] != 0 && s[i] == (char)c)
		return ((char *)(s + i));
	else
		return (NULL);
}
