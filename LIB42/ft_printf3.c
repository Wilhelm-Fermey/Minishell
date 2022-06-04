/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:45:05 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 16:42:37 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*ft_print_hexa_x(const char *s, size_t *charnbr, unsigned int val)
{
	size_t	i;

	if (s[1] == 'x')
		i = ft_to_hexa((long long)val, 'm');
	else
		i = ft_to_hexa((long long)val, 'M');
	(*charnbr) += i;
	return (s + 1);
}

const char	*ft_print_charac(const char *s, size_t *charnbr, char c)
{
	write (1, &c, 1);
	(*charnbr)++;
	return (s + 1);
}

const char	*ft_print_string(const char *s, size_t *charnbr, char *str)
{
	if (str == NULL)
	{
		ft_putstr("(null)");
		(*charnbr) += 6;
	}
	else
	{
		ft_putstr(str);
		(*charnbr) += ft_strlen(str);
	}
	return (s + 1);
}

const char	*ft_print_perc(const char *s, size_t *charnbr)
{
	(*charnbr)++;
	write (1, "%", 1);
	return (s + 1);
}

const char	*ft_specifier(const char *s, va_list all_args, size_t *charnbr)
{
	unsigned long	adress;

	if (*s == '%' && (s[1] == 'd' || s[1] == 'i'))
		s = ft_print_integer(s, charnbr, (int)(va_arg (all_args, int)));
	else if (*s == '%' && s[1] == 'u')
		s = ft_print_unint(s, charnbr, (t_size)(va_arg (all_args, t_size)));
	else if (*s == '%' && s[1] == 'p')
	{
		adress = va_arg(all_args, long long);
		s = ft_print_adress(s, charnbr, adress);
	}
	else if (*s == '%' && (s[1] == 'x' || s[1] == 'X'))
		s = ft_print_hexa_x(s, charnbr, (t_size)(va_arg(all_args, t_size)));
	else if (*s == '%' && s[1] == 'c')
		s = ft_print_charac(s, charnbr, (char)(va_arg(all_args, int)));
	else if (*s == '%' && s[1] == 's')
		s = ft_print_string(s, charnbr, (char *)(va_arg(all_args, char *)));
	else if (*s == '%' && s[1] == '%')
		s = ft_print_perc(s, charnbr);
	return (s);
}
