/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:22:35 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/09 15:17:37 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendest;
	size_t	lensrc;
	size_t	c;

	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	c = 0;
	if (dstsize < lendest + 1)
		return (lensrc + dstsize);
	if (dstsize > lendest + 1)
	{
		while (src[c] != '\0' && lendest + 1 + c < dstsize)
		{
			dst[lendest + c] = src[c];
			c++;
		}
	}
	dst[lendest + c] = '\0';
	return (lendest + lensrc);
}
