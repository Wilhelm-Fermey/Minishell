/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:08:57 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/31 10:09:02 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free (str[i]);
			str[i] = NULL;
			i++;
		}
		free (str);
	}
}

void	free_struc(t_seg **seg)
{
	t_seg	*tmp;
	t_seg	*new_head;


	tmp = *seg;
	while (tmp)
	{
		new_head = tmp->next;
		free_table(tmp->tokens);
		free(tmp->cmd);
		free_table(tmp->input);
		free_table(tmp->output);
		free(tmp->flags);
		free_table(tmp->args);
		free_table(tmp->array);
		free (tmp);
		tmp = new_head;
	}
}

void	free_env(void)
{
	ft_lstclear(g_envp, free);
}
