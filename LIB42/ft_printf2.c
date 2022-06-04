/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:45:05 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 16:38:53 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_for_hexa(unsigned long adress)
{
	int	i;

	i = 0;
	if (adress == 0)
		return (1);
	while (adress > 0)
	{
		i++;
		adress = adress / 16;
	}
	return (i);
}

size_t	ft_to_hexa(unsigned long adress, char c)
{
	char		*str;
	size_t		i;

	i = ft_count_for_hexa(adress);
	str = malloc(i + 1);
	str[i] = '\0';
	i--;
	if (adress == 0)
		str[i] = '0';
	while (adress > 0)
	{
		if (adress % 16 <= 9)
			str[i] = '0' + adress % 16;
		else if (adress % 16 > 9 && c == 'm')
			str[i] = 'a' + adress % 16 - 10;
		else
			str[i] = 'A' + adress % 16 - 10;
		adress = adress / 16;
		i--;
	}
	ft_putstr(str);
	i = ft_strlen(str);
	free(str);
	return (i);
}

void	ft_print_no_spec(const char *s, size_t *charnbr)
{
	write (1, s, 1);
	(*charnbr)++;
}

const char	*ft_print_integer(const char *s, size_t *charnbr, int value)
{
	ft_putnbr((long long)value);
	(*charnbr) += ft_number_of_digits((long long)value);
	return (s + 1);
}

const char	*ft_print_unint(const char *s, size_t *charnbr, unsigned int value)
{
	ft_putnbr(value);
	(*charnbr) += ft_number_of_digits((long long)value);
	return (s + 1);
}
