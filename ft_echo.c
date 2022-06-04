/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:43:05 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/23 14:43:28 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_all_empty(t_seg **seg)
{
	t_seg	*tmp;

	tmp = *seg;
	if (tmp->flags)
	{
		if (tmp->flags[1] == 'n' && tmp->flags[2] == '\0')
			return ;
		else
			printf("%s", tmp->flags + 1);
		printf("\n");
	}
	else
		printf("%s", "\n");
}

void	ft_echo_no_redir(t_seg **seg)
{
	int	i;
	t_seg	*tmp;

	i = 0;
	tmp = *seg;
	if (tmp->flags && tmp->flags[1] == 'n' && tmp->flags[2] == '\0'
		&& tmp->tokens[1][0] == '-')
	{
		while (tmp->args[i])
		{
			ft_printf("%s", tmp->args[i++]);
			if (tmp->args[i])
				ft_printf(" ");
		}
	}
	else
	{
		if (!tmp->flags)
		{
			while (tmp->args[i])
			{
				printf("%s", tmp->args[i++]);
				if (tmp->args[i])
					printf(" ");
			}
			printf("\n");
		}
		else
		{
			i = 1;
			while (tmp->tokens[i])
			{
				if(tmp->tokens[i][0] != '>' && tmp->tokens[i][0] != '<'
					&& !ft_is_not_inout(tmp->tokens[i], tmp))
				{
					if (i > 0)
						printf(" ");
					printf("%s", tmp->tokens[i++]); 
				}
				else 
					i++;
			}
			printf("\n");
		}
	}
}

void	ft_echo(t_seg **seg)
{
	t_seg	*tmp;
	int	i;
	int	new_file;
	int	saved_out;

	tmp = *seg;
	i = -1;
	update_exit_code("0");
	if (tmp->input[0] == NULL && tmp->output[0] == NULL
		&& tmp->args[0] == NULL)
		ft_echo_all_empty(seg);
	else if (tmp->output[0] == NULL)
		ft_echo_no_redir(seg);
	else if	(tmp->output[0])
	{
		while (tmp->output[++i])
		{
			saved_out = dup(1);
			if (tmp->output[i][0] == '1')
				new_file = open(tmp->output[i] + 1, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				new_file = open(tmp->output[i] + 1, O_RDWR | O_APPEND| O_CREAT, 0644);
			dup2(new_file, 1);
			ft_echo_no_redir(seg);
			close(new_file);
			dup2(saved_out, 1);
			close(saved_out);
		}
	}

}
