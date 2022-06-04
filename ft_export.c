/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilhelmfermey <marvin@42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:43:16 by wilhelmfermey     #+#    #+#             */
/*   Updated: 2022/05/25 16:44:21 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(char *str)
{
	char	*val;
	int	i;

	i = 0;
	val = NULL;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		val = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	return (val);
}

void	add_env(char *str)
{
	t_list	*tmp;
	t_list	*prev_tmp;
	char	*last;

	tmp = *g_envp;
	prev_tmp = *g_envp;
	while (tmp->next)
	{
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	prev_tmp->next = NULL;
	last = ft_substr(tmp->content, 0, ft_strlen(tmp->content));
	ft_lstdelone(tmp, free);
	ft_lstadd_back(g_envp, ft_lstnew(str));
	ft_lstadd_back(g_envp, ft_lstnew(last));
}

int	check_name(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]))
			{
				while (str[i] && str[i] != '=')
					i++;
				ft_putstr_fd("export: not valid in this context: ", 2);
				write(2, str, i);
				ft_putstr_fd("\n", 2);
				update_exit_code("1");
				return (0);
			}
			i++;
		}
		return (1);
	}
	else
	{
		if (str[0] == '=')
		{
			ft_putstr_fd("minishell: bad assignment\n", 2);
			update_exit_code("1");
		}
		else
		{
			ft_putstr_fd("export: not an identifier: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\n", 2);
			update_exit_code("1");
		}

		return (0);
	}
}

void	ft_export(t_seg **seg)
{
	t_seg	*tmp;
	int	i;
	char	*val;

	tmp = *seg;
	i = 0;
	update_exit_code("0");
	while (tmp->args[i])
	{
		if (check_name(tmp->args[i]))
		{
			val = find_value(tmp->args[i]);
			if (val)
				add_env(tmp->args[i]);
		}
		i++;
	}
	if (!tmp->args[0])
		ft_env(seg);
}
