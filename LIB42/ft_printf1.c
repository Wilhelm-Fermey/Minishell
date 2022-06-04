/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:45:05 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 11:18:24 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(long long value)
{
	if (value < 0)
	{
		write (1, "-", 1);
		value = -value;
	}	
	if (value >= 10)
	{
		ft_putnbr(value / 10);
		ft_putchar('0' + value % 10);
	}
	else
		ft_putchar('0' + value);
}

size_t	ft_number_of_digits(long long value)
{
	size_t	i;

	i = 0;
	if (value < 0)
	{
		i++;
		value = -value;
	}
	if (value == 0)
		return (1);
	while (value > 0)
	{
		i++;
		value = value / 10;
	}
	return (i);
}
