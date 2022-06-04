/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:45:05 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 16:39:51 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*ft_print_adress(const char *s, size_t *charnbr, unsigned long adr)
{
	size_t	i;

	write (1, "0x", 2);
	i = ft_to_hexa(adr, 'm');
	(*charnbr) += (2 + i);
	return (s + 1);
}

int	ft_printf(const char *s, ...)
{
	size_t			*charnbr;
	size_t			a;
	va_list			all_args;

	charnbr = &a;
	*charnbr = 0;
	va_start (all_args, s);
	while (*s != '\0')
	{
		if (*s != '%')
			ft_print_no_spec(s, charnbr);
		s = ft_specifier(s, all_args, charnbr);
		s++;
	}
	va_end(all_args);
	return (*charnbr);
}
