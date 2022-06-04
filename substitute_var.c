/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zahraa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:41:30 by zahraa            #+#    #+#             */
/*   Updated: 2022/05/31 10:20:38 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sq(char *str, int index)
{
	int	i;
	int	sq;

	i = 0;
	sq = 0;
	while (str[i] && i < index)
	{
		if (str[i] == 39)
			sq++;
		i++;
	}
	if (sq % 2 != 0)
	{
		i = index;
		while (str[i])
		{
			if (str[i] == 39)
				return (1);
			i++;
		}
	}
	return (0);
}

char	*get_var(char *str)
{
	int	i;
	int	len;
	char	*var;

	i = 0;
	len = 0;
	if (str[0] == '?')
	{
		var = ft_strdup("?=");
		return (var);
	}
	while (str[len] && ft_isalnum(str[len]))
		len++;
	var = malloc(len + 2);
	if (!var)
		return (NULL);
	while (i < len)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '=';
	var[++i] = 0;
	return (var);
}

char	*replace_var_envp(char *str, t_list **g_envp, int index)
{
	int	j;
	char	*var;
	char	*new_arg;
	t_list	*tmp;

	new_arg = NULL;
	var = get_var(str + index + 1);
	tmp = (*g_envp);
	while (tmp)
	{
		j = 0;
		if (ft_strstr(tmp->content, var) == tmp->content)
		{
			while (((char *)(tmp->content))[j] != '=')
				j++;
			new_arg = ft_substr(str, 0, index);
			new_arg = ft_strjoin(new_arg, tmp->content + j + 1);
				index = index + ft_strlen(var);
			new_arg = ft_strjoin(new_arg, str + index);

		}
		tmp = tmp->next;
	}
	if (!new_arg)
	{
		new_arg = ft_substr(str, 0, index);
		while (ft_isalnum(str[index + 1]))
			index++;
		new_arg = ft_strjoin(new_arg, str + index);
	}
	free(str);
	free (var);
	return (new_arg);
}

void	replace_var(t_seg **seg, t_list **g_envp)
{
	t_seg	*tmp;
	int	i;
	int	j;

	tmp = *seg;
	while (tmp)
	{
		i = -1;
		j = 0;
		while (tmp->args[++i])
		{
			while (tmp->args[i][j] && tmp->args[i][j] != '$')
				j++;
			if (tmp->args[i][j] && tmp->args[i][j] == '$' && check_sq(tmp->args[i], j) == 0)
				tmp->args[i] = replace_var_envp(tmp->args[i], g_envp, j);
		}
		tmp = tmp->next;
	}
}
