/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkansoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:29:56 by zkansoun          #+#    #+#             */
/*   Updated: 2022/03/18 16:50:08 by zkansoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef unsigned int	t_size;

void		ft_putchar(char c);
size_t		ft_strlen(char *str);
void		ft_putstr(char *str);
void		ft_putnbr(long long value);
size_t		ft_number_of_digits(long long value);
size_t		ft_to_hexa(unsigned long adress, char c);
void		ft_print_no_spec(const char *s, size_t *charnbr);
const char	*ft_print_integer(const char *s, size_t *charnbr, int value);
const char	*ft_print_unint(const char *s, size_t *charnbr, unsigned int value);
const char	*ft_print_adress(const char *s, size_t *charnbr, unsigned long adr);
const char	*ft_print_hexa_x(const char *s, size_t *charnbr, unsigned int val);
const char	*ft_print_charac(const char *s, size_t *charnbr, char c);
const char	*ft_print_string(const char *s, size_t *charnbr, char *str);
const char	*ft_print_perc(const char *s, size_t *charnbr);
const char	*ft_specifier(const char *s, va_list all_args, size_t *charnbr);
int			ft_printf(const char *s, ...);
int			ft_count_for_hexa(unsigned long adress);

#endif
