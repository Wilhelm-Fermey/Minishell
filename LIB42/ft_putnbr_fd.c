/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:35:35 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/17 10:18:17 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	if (nbr != 0)
	{
		if (nbr / 10 > 0)
			ft_putnbr_fd(nbr / 10, fd);
		c = nbr % 10 + 48;
		write(fd, &c, 1);
	}
	if (n == 0)
		write(fd, "0", 1);
}
