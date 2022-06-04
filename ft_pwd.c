/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:11:59 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 10:12:10 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_cases(t_seg **seg)
{
	t_seg	*tmp;
	char	*str;

	tmp = *seg;
	if (!tmp->args[0] && !tmp->flags)
	{
		str = getcwd(NULL, 0);
		if (str)
		{	
			update_exit_code("0");
			ft_printf("%s\n", getcwd(NULL, 0));
		}
		else
			update_exit_code("1");
	}
	else if (!tmp->args[0] && tmp->flags)
	{
		if (!ft_strcmp(tmp->flags, "-LP") || !ft_strcmp(tmp->flags, "-PL")
			|| !ft_strcmp(tmp->flags, "-L") || !ft_strcmp(tmp->flags, "-P"))
		{		
			str = getcwd(NULL, 0);
			if (str)
			{	update_exit_code("0");
				ft_printf("%s\n", getcwd(NULL, 0));
			}
			else
				update_exit_code("1");

		}
		else
		{
			ft_putstr_fd("pwd: bad option: ", 2);
			write(2, tmp->flags, 2);
			ft_putstr_fd("\n", 2);
			update_exit_code("1");
		}
	}
	else
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		update_exit_code("1");
	}
}


void	ft_pwd(t_seg **seg)
{
	t_seg	*tmp;
	int	save_out;
	int	new_file;
	int	i;

	tmp = *seg;
	i = -1;
	if (tmp->output[0] == NULL)
		simple_cases(seg);
	if (!tmp->flags && tmp->output[0])
	{
		while (tmp->output[++i])
		{
			save_out = dup(1);
			if (tmp->output[i][0] == '1')
				new_file = open(tmp->output[i] + 1, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				new_file = open(tmp->output[i] + 1, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(new_file, 1);
			simple_cases(seg);
			close(new_file);
			dup2(save_out, 1);
			close(save_out);
		}

	}
}
