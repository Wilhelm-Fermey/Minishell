/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:10:30 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 10:10:43 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_seg **seg)
{
	t_seg	*tmp;
	int	save_out;
	int	new_file;
	int	i;

	tmp = *seg;
	update_exit_code("0");
	if (tmp->args[0])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(tmp->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		update_exit_code("127");
	}
	else if (!tmp->output[0])
			ft_print_list(&((*g_envp)->next));
	else if (tmp->output[0])
	{
		i = -1;
		while (tmp->output[++i])
		{
			save_out = dup(1);
			if (tmp->output[i][0] == '1')
				new_file = open(tmp->output[i] + 1, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				new_file = open(tmp->output[i] + 1, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(new_file, 1);
			ft_print_list(&((*g_envp)->next));
			close(new_file);
			dup2(save_out, 1);
			close(save_out);
		}
	}
}
