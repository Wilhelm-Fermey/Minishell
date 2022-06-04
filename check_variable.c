/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfermey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:28:44 by wfermey           #+#    #+#             */
/*   Updated: 2022/05/31 10:43:52 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rm_quote_and_$(char *str)
{
	int	i;
	int	j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	res = malloc(i * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '$' && str[i] != '"')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	return (res);
}

char	*ft_change_variable(char *str, char **envp)
{
	int	i;
	int	j;
	char	*res;

	i = 0;
	j = 0;
	str = ft_rm_quote_and_$(str);
	while (!ft_strstr(envp[i], str))
		i++;
	while (envp[i][j] != '=')
		j++;
	j++;
	res = ft_strdup(&envp[i][j]);
	free (str);
	return (res);
}

void	ft_check_variable(t_seg **seg, char **envp)
{
	t_seg	*tmp;
	int		i;

	tmp = *seg;
	while (tmp)
	{
		i = 0;
		while(tmp->args[i])
		{
			if (ft_strstr(tmp->args[i], "\"$"))
				tmp->args[i] = ft_change_variable(tmp->args[i], envp);
			i++;
		}
		tmp = tmp->next;
	}
}

int	check_seg(t_seg **seg)
{
	t_seg	*tmp;

	tmp = *seg;
	while (tmp)
	{
		int	i;
		i = 0;
		if (!tmp->cmd)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->tokens[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			update_exit_code("127");
			return (1);
		}
		while (tmp->tokens[i] && ft_strcmp(tmp->tokens[i], tmp->cmd))
		{
			if (!ft_is_not_inout(tmp->tokens[i], tmp))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->tokens[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				update_exit_code("127");
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_line_space(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == ' ' || (str[i] >= '\b' && str[i] <= '\r'))
				i++;
			else
				return (1);
		}
	}
	return (0);
}
