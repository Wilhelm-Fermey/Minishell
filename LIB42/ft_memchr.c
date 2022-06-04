/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:42:02 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/09 17:04:44 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cpy;

	cpy = (unsigned char *)s;
	if (!n)
		return (NULL);
	while (*cpy != (unsigned char)c)
	{
		if (!--n)
			return (NULL);
		else
			cpy++;
	}
	return ((void *)(cpy));
}
