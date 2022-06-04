/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:10:40 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/17 10:14:39 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	*ft_illoc(int nbr, int *j)
{
	char	*str;

	*j = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		*j = *j + 1;
	}
	if (nbr == 0)
		*j = 1;
	while (nbr)
	{
		nbr /= 10;
		*j = *j + 1;
	}
	str = (char *)malloc(*j + 1);
	if (!str)
		return (NULL);
	str[*j] = '\0';
	return (str);
}

static	void	ft_recnbr(int n, char *nbr, int j)
{
	if (n == -2147483648)
	{
		n = -214748364;
		nbr[--j] = '8';
	}
	if (n < 0)
	{
		n *= -1;
		nbr[0] = '-';
	}
	if (n == 0)
		nbr[0] = '0';
	while (n > 9)
	{
		nbr[--j] = (n % 10) + 48;
		n /= 10;
	}
	nbr[--j] = n + 48;
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		j;

	nbr = ft_illoc(n, &j);
	if (!nbr)
		return (NULL);
	ft_recnbr(n, nbr, j);
	return (nbr);
}
