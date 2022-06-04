/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:10:59 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 10:11:06 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_seg **seg)
{
	t_seg *tmp;
	int	i;
	int	exit_code;

	tmp = *seg;
	i = 0;
	if (!tmp->args[0])
	{
		free_struc(seg);
		free_env();
		exit (0);
	}
	else if(tmp->args[0] && !tmp->args[1])
	{
		while (tmp->args[0][i])
		{
			if (ft_isdigit(tmp->args[0][i]))
			{
				free_struc(seg);
				free_env();
				exit(255);
			}
			i++;
		}
		exit_code = ft_atoi(tmp->args[0]);
		free_struc(seg);
		free_env();
		exit (exit_code);
	}
	else
		ft_putstr_fd("exit: too many arguments\n", 2);
	
}
