/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfermey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:20:59 by wfermey           #+#    #+#             */
/*   Updated: 2022/05/31 13:19:07 by wilhelmfermey    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_even(t_seg **seg)
{
	t_seg	*tmp;
	int		i[2];
	int		count;

	tmp = *seg;
	while (tmp)
	{
		i[0] = -1;
		count = 0;
		while (tmp->args[++i[0]])
		{
			i[1] = -1;
			while(tmp->args[i[0]][++i[1]])
			{
				if (tmp->args[i[0]][i[1]] == '"')
					count++;
			}
		}
		if (count % 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_even2(t_seg **seg)
{
	t_seg	*tmp;
	int		i[2];
	int		count;

	tmp = *seg;
	while (tmp)
	{
		i[0] = -1;
		count = 0;
		while (tmp->args[++i[0]])
		{
			i[1] = -1;
			while(tmp->args[i[0]][++i[1]])
			{
				if (tmp->args[i[0]][i[1]] == '\'')
					count++;
			}
		}
		if (count % 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_rm_quote(char *str)
{
	char	*res;

	if ((str[0] == 34 && str[ft_strlen(str) - 1] == 34)
		|| (str[0] == 39 && str[ft_strlen(str) - 1] == 39))
	{
		res = ft_substr(str, 1, ft_strlen(str) - 2);
		free(str);
		return (res);
	}
	else
		return (str);
}

void	ft_rm(t_seg **seg)
{
	t_seg	*tmp;
	int		i;

	tmp = *seg;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			tmp->args[i] = ft_rm_quote(tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	check_args(t_seg **seg)
{
	if (ft_even(seg) || ft_even2(seg))
	{
		printf("Quotes must be closed");
		return (1);
	}
	ft_rm(seg);
	return (0);	
}
