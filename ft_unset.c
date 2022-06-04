/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:45:40 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/25 16:45:45 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_unset(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) || str[0] == '-')
	{
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]))
			{
				ft_putstr_fd("unset: ", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd(": invalid parameter name\n", 2);
				return (0);
			}
			i++;
		}
	}
	else
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
		return (0);
	}
	return (1);
}

void	ft_unset(t_seg **seg)
{
	t_seg *tmp;
	int	i;

	tmp = *seg;
	i = 0;
	if (!tmp->args[0])
		ft_putstr_fd("unset: not enough arguments\n", 2);
	while (tmp->args[i])
	{
		if (check_name_unset(tmp->args[i]))
			del_content(g_envp, tmp->args[i]);
		i++;
	}
	
}
